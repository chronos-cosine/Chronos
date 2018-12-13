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

#include "Apps/Sorter/Services/DataProviders/MultiPatternMatcher.h"
#include "Collections/Concurrent/Map.h"

#include <memory>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
                    
            MultiPatternMatcher::MultiPatternMatcher(
                    const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns) 
              : m_matcher(t_patterns), 
                Notifier::Notifiable() {
                m_matcher.match_found = m_match_found;
            }
            
            MultiPatternMatcher::MultiPatternMatcher(
                    const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier) 
              : m_matcher(t_patterns), 
                Notifier::Notifiable(t_notifier) {
                notify("MultiPatternMatcher::MultiPatternMatcher()");
                
                m_matcher.match_found = m_match_found;
            }
            
            void 
            MultiPatternMatcher::match_found::operator()(
                    MultiPatternMatcher* t_sender, 
                    const std::shared_ptr<Sorter::Models::Job>& t_job,
                    const unsigned long long& t_position,
                    const std::set<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns) {
                t_sender->notify("MultiPatternMatcher::match_found::operator()");
                
                for (auto& pattern: t_patterns) {
                    bool found = false;
                    for (auto& result: t_job->results) {
                        if (*result->job == *t_job
                            && *result->bin == *pattern->bin) {
                            result->pattern_matches[pattern].insert(t_position);
                            found = true;
                            break;
                        }
                    }
                    
                    if (!found) {
                        auto result = std::make_shared<Sorter::Models::Result>();
                        result->job = t_job;
                        result->bin = pattern->bin;
                        result->pattern_matches[pattern].insert(t_position);
                        t_job->results.insert(result);
                    }
                } 
            }

            void 
            MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& t_job) {
                notify("MultiPatternMatcher::process()");
                
                m_matcher.match(t_job, this);
            }
            
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 