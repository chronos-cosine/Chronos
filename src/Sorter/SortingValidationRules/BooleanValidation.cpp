/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BooleanMatch.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 04 November 2018, 1:59 PM
 */

#include "Sorter/SortingRules/BooleanMatch.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Pattern.h"

#include <algorithm>
#include <memory>
#include <map>
#include <set>

namespace Sorter {
    
    namespace SortingValidationRules {
        
        BooleanValidation::BooleanValidation(
                const std::shared_ptr<std::map<unsigned long long, Pattern>>& patterns,
                const std::shared_ptr<std::map<unsigned long long, Bin>>& bins,
                const std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, std::set<Pattern>>>>& bin_patterns)
            : __patterns(patterns), __bins(bins), __bin_patterns(bin_patterns) {
        }
        
        void 
        BooleanValidation::match(std::map<unsigned long long, 
                                     std::set<Sorter::Pattern>>& position_pattern_matches,
                            std::set<Sorter::Bin>& bin_matches) {
            std::set<Pattern> temp_patterns;
            for (const auto& pair: position_pattern_matches) {
                for (const auto& pattern: pair.second) {
                    temp_patterns.insert(pattern);
                }
            }
        
            for (const auto& pattern: temp_patterns) {
                auto bin = __bins[pattern.bin_id];
                // skip if match already excluded
                if (bin_matches.end() == bin_matches.find(bin)) {
                    continue;
                }
                
                // remove if match is not
                if (pattern.boolean_operator == Sorter::BooleanOperator::NOT) {
                    bin_matches.erase(bin_matches.find(bin));
                    continue;
                }

                // remove if at least 1 or match required
                auto no_bin_pattern = (*__bin_patterns)[pattern.bin_id].end();
                if ((*__bin_patterns)[pattern.bin_id].find(Sorter::BooleanOperator::OR) != no_bin_pattern
                    && pattern.boolean_operator == Sorter::BooleanOperator::AND) {
                    bin_matches.erase(bin_matches.find(bin));
                    continue;
                }

                // remove if not all ands matched
                auto and_iterator = (*__bin_patterns)[pattern.bin_id].find(Sorter::BooleanOperator::AND);
                if (and_iterator != no_bin_pattern) {
                    for(auto iter = (*and_iterator).second.begin();
                        iter != (*and_iterator).second.end();
                        ++iter) {
                        if (temp_patterns.end() == temp_patterns.find(*iter)) {
                            bin_matches.erase(bin_matches.find(bin));
                            break;
                        }
                    } 
                }
            }
        }
        
    } /* namespace SortingValidationRules */
    
} /* namespace Sorter */