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
#include "Collections/Concurrent/Map.h"

#include <iostream>
#include <memory>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
        
            MultiPatternMatcher::MultiPatternMatcher(
                const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns) 
                : __matcher(patterns) {
                std::cout << "MultiPatternMatcher::MultiPatternMatcher()" << std::endl;

                __matcher.match_found = __match_found;
            }

            void 
            MultiPatternMatcher::match_found::operator()(
                    MultiPatternMatcher* sender, 
                    const std::shared_ptr<Sorter::Models::Job>& job,
                    const unsigned long long& position,
                    const std::set<std::shared_ptr<Sorter::Models::Pattern>>& patterns) {
                std::cout << sender << "MultiPatternMatcher::match_found::operator()" << std::endl;
                
                for (auto& pattern: patterns) {
                    std::cout << "MultiPatternMatcher::match_found::operator() pattern loop" << std::endl;
                    auto result = std::make_shared<Sorter::Models::Result>();
                    result->job = job;
                    result->bin = pattern->bin;
                    result->pattern_matches[pattern].insert(position);
                    
                    auto iter = job->results.find(result);
                    if (iter == job->results.end()) {
                        job->results.insert(result);
                    }
                    else {
                        (*iter)->pattern_matches[pattern].insert(position);
                    }
                } 
                std::cout << "MultiPatternMatcher::match_found::operator()4" << std::endl;
            }

            void 
            MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                std::cout << "MultiPatternMatcher::process()" 
                          << std::endl;
                __matcher.match(job, this);
            }
          
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 