/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 1:13 PM
 */

#include "Collections/ConcurrentQueue.h"
#include "SortingMachine.h"
#include "File/DataReader.h"
#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"
#include "Sorter/Result.h"
#include "Sorter/Settings.h"
#include "Notifier/CoutNotifier.h"

#include <experimental/filesystem>
#include <exception>
#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    
    SortingMachine::~SortingMachine() {
    }
    
    SortingMachine::SortingMachine(const std::shared_ptr<Settings>& settings) 
        : Processors::IProcessor(), 
          __settings(settings), __completed(this), __match_found(this),
          __jobs(std::make_shared<Collections::ConcurrentQueue<std::string>>()) {
        initialise();
    } 
    
    SortingMachine::SortingMachine(const std::shared_ptr<Settings>& settings, 
            const std::shared_ptr<Notifier::INotifier>& notifier)  
        : Processors::IProcessor(30, notifier),
          __settings(settings), __completed(this), 
          __match_found(this),
          __jobs(std::make_shared<Collections::ConcurrentQueue<std::string>>()) {
        initialise();
    }
    
    SortingMachine::completed::completed(SortingMachine* sm) 
            : sorting_machine(sm) {
    }
    
    SortingMachine::match_found::match_found(SortingMachine* sm) 
            : sorting_machine(sm) {
    } 
    
    void
    SortingMachine::completed::operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& total_matches) {
        if (sorting_machine->is_boolean_match(input)
            && sorting_machine->is_bin_hierarchy_match(input)) {
            Result result;
            result.job = const_cast<Job*>(&input);
            result.bin_matches = const_cast<std::set<Bin>*>(&(sorting_machine->__bin_matches[input]));
            result.pattern_matches = const_cast<std::map<unsigned long long, 
                    std::set<Pattern>>*>(&(sorting_machine->__pattern_matches[input]));
            
        }
        
        fs::path p(input.filename);
        std::stringstream new_filename;
        new_filename << sorting_machine->__settings->completed_directory 
                     << p.stem().c_str()
                     << sorting_machine->__settings->completed_extension;

        fs::rename(p, fs::path(new_filename.str()));
        sorting_machine->__pattern_matches.erase(input);
        sorting_machine->__bin_matches.erase(input);
    } 
    
    void SortingMachine::match_found::operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& position,
                const std::set<Pattern>& patterns) {
        for (const Pattern& pattern: patterns) {
            sorting_machine->__pattern_matches[input][position].insert(pattern); 
            sorting_machine->__bin_matches[input]
                .insert(sorting_machine->__bins[pattern.bin_id]);
        }
    } 
     
    bool
    SortingMachine::is_bin_hierarchy_match(const Job& input) {
        if (__bin_matches.end() == __bin_matches.find(input)) {
            return false;
        }
        
        Bin parent = *(__bin_matches[input].begin());
        while (parent.parent_id != 0) {
            parent = __bins[parent.parent_id]; 
            
            if (__bin_patterns.end() != __bin_patterns.find(parent.id)) {
                if (__bin_patterns[parent.id].size() > 0) {
                    if (__bin_matches[input].end() == __bin_matches[input].find(parent)) {
                        return false;
                    }
                } else {
                    __bin_matches[input].insert(parent);
                }
            } else {
                __bin_matches[input].insert(parent);
            }
        }
        
        return true;
    } 
    
    bool 
    SortingMachine::is_boolean_match(const Job& input) {
        if (__pattern_matches.end() == __pattern_matches.find(input)) {
            return false;
        }
        
        std::set<Pattern> temp_patterns;
        for (const auto& pair: __pattern_matches[input]) {
            for (const auto& pattern: pair.second) {
                temp_patterns.insert(pattern);
            }
        }
        
        for (const Pattern& pattern: temp_patterns) {
            //not
            if (pattern.boolean_operator == BooleanOperator::NOT) {
                return false;
            }
            
            //or
            if (__bin_patterns[pattern.bin_id].end() 
                    != __bin_patterns[pattern.bin_id].find(BooleanOperator::OR)
                && pattern.boolean_operator == BooleanOperator::AND) {
                return false;
            }
            
            //and
            std::map<BooleanOperator, std::set<Pattern>>::const_iterator and_iterator 
                    = __bin_patterns[pattern.bin_id].find(BooleanOperator::AND);
            if (__bin_patterns[pattern.bin_id].end() 
                    != and_iterator) {
                for(std::set<Pattern>::iterator iter = (*and_iterator).second.begin();
                    iter != (*and_iterator).second.end();
                    ++iter) {
                    if (temp_patterns.end() == temp_patterns.find(*iter)) {
                        return false;
                    }
                } 
            }
        }
        
        return true;
    }
        
    void
    SortingMachine::initialise_bins(const std::vector<Bin>& bins) {
        for (const Bin& bin: bins) {
            __bins[bin.id] = bin;
        }
    }
    
    void
    SortingMachine::initialise_patterns(const std::vector<Pattern>& patterns) {
        for (const Pattern& pattern: patterns) {
            if (pattern.bin_id > 0) {
                __bin_patterns[pattern.bin_id][pattern.boolean_operator]
                    .insert(pattern);
            }
            __patterns[pattern.id] = pattern;
        }
    }
    
    void
    SortingMachine::initialise_spoolers() {
        for (const auto& directory: __settings->job_file_directories) {
            std::shared_ptr<File::Spooler> spooler = std::make_shared<File::Spooler>(
                directory,
                __settings->trigger_extension,
                __settings->busy_extension,
                __jobs);
            __spoolers.push_back(std::move(spooler));
        }
    }
    
    void 
    SortingMachine::initialise_sorters() {
        for (unsigned short i = 0; i < __settings->instances; ++i) {
            std::shared_ptr<Sorter> sorter = std::make_shared<Sorter>(
                __matcher,
                __jobs,
                Processors::IProcessor::notifier);
            __sorters.push_back(std::move(sorter));
        }
    }
    
    bool
    SortingMachine::process() {
        return false;
    }
    
    void 
    SortingMachine::start() {
        notify("SortingMachine::start()");
        
        for (auto& spooler: __spoolers) {
            std::thread thread(&File::Spooler::start, spooler);
            thread.detach();
            
            __spooler_threads.push_back(std::move(thread));
        }
        
        for (auto& sorter: __sorters) {
            std::thread thread(&Sorter::start, sorter);
            thread.detach();
            
            __sorter_threads.push_back(std::move(thread));
        }
        
        Processors::IProcessor::start();
    }
    
    void 
    SortingMachine::stop() {
        notify("SortingMachine::stop()");
        
        for (auto& spooler: __spoolers) {
            spooler->stop();
        }
        for (auto& sorter: __sorters) {
            sorter->stop();
        }
        
        __spooler_threads.clear();
        __sorter_threads.clear();
        
        Processors::IProcessor::stop();
    }
     
    void 
    SortingMachine::initialise_matcher(const std::vector<Pattern>& patterns) {
        __matcher = std::make_shared<PatternMatcher::PatternMatchingMachine
                <Job, Pattern, Sorter>>(patterns);
        __matcher->completed = __completed;
        __matcher->match_found = __match_found;
    }
    
    void 
    SortingMachine::initialise() {
        notify("SortingMachine::initialise()");
        
        std::vector<Bin> bins = File::DataReader::read<Bin>(__settings->bins_path, 
                __settings->bins_file_type);
        std::vector<Pattern> patterns = File::DataReader::read<Pattern>(
                __settings->patterns_path, 
                __settings->patterns_file_type);
        
        initialise_matcher(patterns); 
        initialise_bins(bins);
        initialise_patterns(patterns);
        initialise_spoolers();
        initialise_sorters(); 
        
    } /* initialise() */
    
} /* namespace Sorter */

