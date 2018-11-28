/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MultiPatternMatcher.h
 * Author: user
 *
 * Created on 21 November 2018, 1:29 PM
 */

#ifndef SORTER_SERVICES_DATAPROVIDERS_MULTIPATTERNMATCHER_H
#define SORTER_SERVICES_DATAPROVIDERS_MULTIPATTERNMATCHER_H

#include "Collections/IMap.h"
#include "Notifier/INotifier.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Models/Pattern.h"
#include "Sorter/Models/Result.h"
#include "Sorter/Services/IDataProvider.h"

#include <memory>
#include <set>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
    
            class MultiPatternMatcher : public IDataProvider {
                struct match_found {
                    void operator()(
                        MultiPatternMatcher* sender, 
                        const std::shared_ptr<Sorter::Models::Job>& input,
                        const unsigned long long& position,
                        const std::set<std::shared_ptr<Sorter::Models::Pattern>>& patterns);
                }; /* struct match_found */
            public:
                virtual ~MultiPatternMatcher() = default;
                MultiPatternMatcher(const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns,
                           const std::shared_ptr<Notifier::INotifier>& notifier); 
                MultiPatternMatcher(const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& patterns); 

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& job);
            private:
                void init();
                void notify(const std::string& message);
            private:
                match_found __match_found;
                PatternMatcher::PatternMatchingMachine<Sorter::Models::Job, 
                                                       Sorter::Models::Pattern,
                                                       MultiPatternMatcher> __matcher;
                std::shared_ptr<Notifier::INotifier> __notifier;

            }; /* class MultiPatternMatcher */ 
    
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 

#endif /* SORTER_SERVICES_DATAPROVIDERS_MULTIPATTERNMATCHER_H */

