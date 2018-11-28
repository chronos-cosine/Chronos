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

#include "Sorter/Services/DataProviders/MultiPatternMatcher.h"
#include "Collections/Concurrent/Map.h"

#include <iostream>
#include <memory>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
                    
            MultiPatternMatcher::MultiPatternMatcher(
                    const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns,
                    const std::shared_ptr<Notifier::INotifier>& notifier) 
                : __matcher(patterns), 
                  __notifier(notifier) {
                notify("MultiPatternMatcher::MultiPatternMatcher()");
                
                __matcher.match_found = __match_found;
            }
            
            MultiPatternMatcher::MultiPatternMatcher(
                const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns) 
                : __matcher(patterns), 
                  __notifier(nullptr) {
                __matcher.match_found = __match_found;
            }
            
            void 
            MultiPatternMatcher::match_found::operator()(
                    MultiPatternMatcher* sender, 
                    const std::shared_ptr<Sorter::Models::Job>& job,
                    const unsigned long long& position,
                    const std::set<std::shared_ptr<Sorter::Models::Pattern>>& patterns) {
                sender->notify("MultiPatternMatcher::match_found::operator()");
                
                for (auto& pattern: patterns) {
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
            }

            void 
            MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                notify("MultiPatternMatcher::process()");
                
                __matcher.match(job, this);
            }
            
            void 
            MultiPatternMatcher::notify(const std::string& message) {
                if (nullptr != __notifier) {
                    __notifier->notify(message);
                }
            }
          
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 