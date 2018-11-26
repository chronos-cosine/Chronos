/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiPatternMatcher.cpp
 * Author: user
 * 
 * Created on 21 November 2018, 1:29 PM
 */

#include "MultiPatternMatcher.h"

#include <iostream>
#include <memory>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
        
            MultiPatternMatcher::MultiPatternMatcher(
                const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns) 
                : __matcher(patterns) {
                
                std::cout << "MultiPatternMatcher::MultiPatternMatcher()" 
                          << std::endl;

                __matcher.match_found = __match_found;
            }

            void 
            MultiPatternMatcher::match_found::operator()(
                const std::shared_ptr<MultiPatternMatcher>& sender, 
                const std::shared_ptr<Sorter::Models::Job>& input,
                const unsigned long long& position,
                const std::set<std::shared_ptr<Sorter::Models::Pattern>>& patterns) {

                std::cout << "MultiPatternMatcher::match_found::operator()" 
                          << std::endl;
                        
                if (!sender->__results->exist(input)) {
                    sender->__results->insert(input, 
                        std::set<std::shared_ptr<Sorter::Models::Result>>());
                }

                for (auto& pattern: patterns) {
                    auto result = std::make_shared<Sorter::Models::Result>();
                    result->job = input;
                    result->bin = pattern->bin;
                    result->pattern_matches[pattern].insert(position);

                    auto iter = sender->__results->at(input).find(result);
                    if (iter != sender->__results->at(input).end()) {
                        (*iter)->pattern_matches[pattern].insert(position);
                    } else {
                        sender->__results->at(input).insert(std::move(result));
                    }
                } 
            }

            void 
            MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                std::cout << "MultiPatternMatcher::process()" 
                          << std::endl;
                __matcher.match(job, std::enable_shared_from_this<
                                        MultiPatternMatcher>::shared_from_this());
            }
          
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 