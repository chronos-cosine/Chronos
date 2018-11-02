/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/SortingMachine.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 30 October 2018, 1:13 PM
 */

#include "File/JsonDataWriter.h"
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
                const Job& job,
                const unsigned long long& total_matches) {
        std::string message;
        if (sorting_machine->is_boolean_match(job)
            && sorting_machine->is_bin_hierarchy_match(job)) {
            
            message = "SortingMachine::completed result found for " + std::to_string(job.id);
            sorting_machine->notify(message);
            Result result;
            result.job = const_cast<Job*>(&job);
            result.bin_matches = &(sorting_machine->__bin_matches[job]);
            result.pattern_matches = &(sorting_machine->__pattern_matches[job]);
            
            std::stringstream result_file;
            result_file << sorting_machine->__settings->result_output_directory
                        << job.id
                        << sorting_machine->__settings->match_extension;
            
            if (fs::exists(result_file.str())) {
                fs::remove(result_file.str());
            }
            File::JsonDataWriter<Result>::write(result, result_file.str());
            
            message = "SortingMachine::completed resuls written " + 
                                  std::to_string(job.id);
            sorting_machine->notify(message);
        }
        
        fs::path p(job.filename);
        std::stringstream new_filename;
        new_filename << sorting_machine->__settings->completed_directory 
                     << p.stem().c_str()
                     << sorting_machine->__settings->completed_extension;

        message = "SortingMachine::completed moving file to complete " + 
                              std::to_string(job.id);
        sorting_machine->notify(message);

        if (fs::exists(new_filename.str())) {
            fs::remove(new_filename.str());
        }
        fs::rename(p, new_filename.str());
        sorting_machine->__pattern_matches.erase(job);
        sorting_machine->__bin_matches.erase(job);
        
        message = "SortingMachine::completed cleared maps " + 
                              std::to_string(job.id);
        sorting_machine->notify(message);
    } 
    
    void SortingMachine::match_found::operator()(Sorter* sender, 
                const Job& job,
                const unsigned long long& position,
                const std::set<Pattern>& patterns) {
        for (const Pattern& pattern: patterns) {
            sorting_machine->__pattern_matches[job][position].insert(pattern); 
            sorting_machine->__bin_matches[job]
                .insert(sorting_machine->__bins[pattern.bin_id]);
        }
    } 
     
    bool
    SortingMachine::is_bin_hierarchy_match(const Job& job) {
        if (__bin_matches.end() == __bin_matches.find(job)) {
            return false;
        }
        
        Bin parent = *(__bin_matches[job].begin());
        while (parent.parent_id != 0) {
            parent = __bins[parent.parent_id]; 
            
            if (__bin_patterns.end() != __bin_patterns.find(parent.id)) {
                if (__bin_patterns[parent.id].size() > 0) {
                    if (__bin_matches[job].end() == __bin_matches[job].find(parent)) {
                        return false;
                    }
                } else {
                    __bin_matches[job].insert(parent);
                }
            } else {
                __bin_matches[job].insert(parent);
            }
        }
        
        return true;
    } 
    
    bool 
    SortingMachine::is_boolean_match(const Job& job) {
        if (__pattern_matches.end() == __pattern_matches.find(job)) {
            return false;
        }
        
        std::set<Pattern> temp_patterns;
        for (const auto& pair: __pattern_matches[job]) {
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
            std::unique_ptr<File::Spooler> spooler = std::make_unique<File::Spooler>(
                directory,
                __settings->trigger_extension,
                __settings->busy_extension,
                10,
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
    
    void 
    SortingMachine::reset_job_directory() {
        notify("SortingMachine::reset_job_directory()");
        
        for (const std::string& directory: __settings->job_file_directories) {
            for (const auto& p: fs::directory_iterator(directory)) {
                if (p.path().extension() == __settings->busy_extension) {
                    std::stringstream new_filename;
                    new_filename << directory
                                 << p.path().stem().c_str()
                                 << __settings->trigger_extension;

                    try {
                        fs::rename(p, fs::path(new_filename.str()));
                    } catch (const fs::filesystem_error& e) {
                        throw std::runtime_error(
                            "SortingMachine::reset_job_directory() unable to reset file");
                    }
                }
            }
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
        
        std::unique_ptr<std::vector<Bin>> bins 
            = File::DataReader<Bin>::read(__settings->bins_path, 
                __settings->bins_file_type);
        std::unique_ptr<std::vector<Pattern>> patterns 
            = File::DataReader<Pattern>::read(
                __settings->patterns_path, 
                __settings->patterns_file_type);
        
        reset_job_directory();
        initialise_matcher(*patterns); 
        initialise_bins(*bins);
        initialise_patterns(*patterns);
        initialise_spoolers();
        initialise_sorters(); 
        
    } /* initialise() */
    
} /* namespace Sorter */

