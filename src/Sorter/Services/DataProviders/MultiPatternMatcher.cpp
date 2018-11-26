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

namespace Sorter {
    namespace Services {
        namespace DataProviders {
        
            MultiPatternMatcher::match_found::match_found(const std::shared_ptr<MultiPatternMatcher>& sender)
                : __sender(sender) {
            }

            void 
            MultiPatternMatcher::match_found::operator()(
                const std::shared_ptr<MultiPatternMatcher>& sender, 
                const std::shared_ptr<Sorter::Models::Job>& input,
                const unsigned long long& position,
                const std::set<std::shared_ptr<Sorter::Models::Pattern>>& patterns) {

                if (!__sender->__results->exist(input)) {
                    __sender->__results->insert(input, 
                        std::set<std::shared_ptr<Sorter::Models::Result>>());
                }

                for (auto& pattern: patterns) {
                    auto result = std::make_shared<Sorter::Models::Result>();
                    result->job = input;
                    result->bin = pattern->bin;
                    result->pattern_matches[pattern].insert(position);

                    auto iter = __sender->__results->at(input).find(result);
                    if (iter != __sender->__results->at(input).end()) {
                        (*iter)->pattern_matches[pattern].insert(position);
                    } else {
                        __sender->__results->at(input).insert(std::move(result));
                    }
                } 
            }

            MultiPatternMatcher::MultiPatternMatcher(
                const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns) 
                : __matcher(patterns), 
                  match_found(std::enable_shared_from_this<
                     MultiPatternMatcher>::shared_from_this()) {
                __matcher.match_found = match_found;
            }

            void 
            MultiPatternMatcher::process(const std::shared_ptr<Sorter::Models::Job>& job) {
                __matcher.match(job, std::enable_shared_from_this<
                                        MultiPatternMatcher>::shared_from_this());
            }
          
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 