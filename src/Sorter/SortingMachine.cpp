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

#include <exception>
#include <map>
#include <set>
#include <iostream>

namespace Sorter {
    
    SortingMachine::~SortingMachine() {
    }
    
    SortingMachine::SortingMachine(const std::shared_ptr<Settings>& settings) 
        : __settings(settings), __completed(this), __match_found(this),
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
            result.pattern_matches = const_cast<std::set<Pattern>*>(&(sorting_machine->__pattern_matches[input]));
            
            std::cout << result << std::endl;
        }
        
        sorting_machine->__pattern_matches.erase(input);
        sorting_machine->__bin_matches.erase(input);
    } 
    
    void SortingMachine::match_found::operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& position,
                const std::set<Pattern>& patterns) {
        for (const Pattern& pattern: patterns) {
            sorting_machine->__pattern_matches[input].insert(pattern); 
            sorting_machine->__bin_matches[input]
                .insert(sorting_machine->__bins[pattern.bin_id]);
        }
    } 
     
    bool
    SortingMachine::is_bin_hierarchy_match(const Job& input) {
        Bin parent = *(__bin_matches[input].begin());
        
        while (parent.parent_id != 0) {
            parent = __bins[parent.parent_id];
            
            if (__bin_matches[input].end() == __bin_matches[input].find(parent)) {
                return false;
            }
        }
        
        return true;
    } 
    
    bool 
    SortingMachine::is_boolean_match(const Job& input) {
        for (const Pattern& pattern: __pattern_matches[input]) {
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
                    if (__pattern_matches[input].end() 
                            == __pattern_matches[input].find(*iter)) {
                        return false;
                    }
                } 
            }
        }
        
        return true;
    } 
    
    void 
    SortingMachine::initialise() {
        std::vector<Bin> bins = File::DataReader::read<Bin>(__settings->bins_path, 
                __settings->bins_file_type);
        std::vector<Pattern> patterns = File::DataReader::read<Pattern>(__settings->patterns_path, 
                __settings->patterns_file_type);
        
        __matcher = std::make_shared<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>>(patterns);
        __matcher->completed = __completed;
        __matcher->match_found = __match_found;
        
        for (Bin& bin: bins) {
            unsigned long long bin_id = bin.id;
            __bins[bin_id] = bin;
        }
        for (Pattern& pattern: patterns) {
            if (pattern.bin_id > 0) {
                __bin_patterns[pattern.bin_id][pattern.boolean_operator].insert(pattern);
            }
            __patterns[pattern.id] = pattern;
        }
    } /* initialise() */
    
} /* namespace Sorter */

