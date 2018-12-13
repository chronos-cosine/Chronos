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
#include "Notifier/Notifiable.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Apps/Sorter/Models/Bin.h"
#include "Apps/Sorter/Models/Job.h"
#include "Apps/Sorter/Models/Pattern.h"
#include "Apps/Sorter/Models/Result.h"
#include "Apps/Sorter/Services/IDataProvider.h"

#include <memory>
#include <set>
#include <string>

namespace Sorter {
    namespace Services {
        namespace DataProviders {
    
            class MultiPatternMatcher : public IDataProvider,
                                        public Notifier::Notifiable {
                struct match_found {
                    void operator()(
                        MultiPatternMatcher* t_sender, 
                        const std::shared_ptr<Sorter::Models::Job>& t_input,
                        const unsigned long long& t_position,
                        const std::set<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns);
                }; /* struct match_found */
            public:
                virtual ~MultiPatternMatcher() = default;
                MultiPatternMatcher(const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns,
                           const std::shared_ptr<Notifier::INotifier>& t_notifier); 
                MultiPatternMatcher(const std::vector<std::shared_ptr<Sorter::Models::Pattern>>& t_patterns); 

                virtual void process(const std::shared_ptr<Sorter::Models::Job>& t_job);
            private:
                void init();
            private:
                match_found m_match_found;
                PatternMatcher::PatternMatchingMachine<Sorter::Models::Job, 
                                                       Sorter::Models::Pattern,
                                                       MultiPatternMatcher> m_matcher;

            }; /* class MultiPatternMatcher */ 
    
        } /* namespace DataProviders */
    } /* namespace Services */
} /* namespace Sorter */ 

#endif /* SORTER_SERVICES_DATAPROVIDERS_MULTIPATTERNMATCHER_H */

