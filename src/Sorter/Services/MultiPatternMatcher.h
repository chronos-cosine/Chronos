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

#ifndef SORTER_SERVICES_MULTIPATTERNMATCHER_H
#define SORTER_SERVICES_MULTIPATTERNMATCHER_H

#include "Collections/IMap.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Services/IDataProvider.h"

#include <memory>

namespace Sorter {
    namespace Services {
    
        class MultiPatternMatcher : public IDataProvider {
        public:
            virtual ~MultiPatternMatcher() = default;
            MultiPatternMatcher() = default; 
            
            virtual void process(const std::shared_ptr<Sorter::Models::Job>& job);
        private:
            PatternMatcher::PatternMatchingMachine<> __matcher;
            std::shared_ptr<Collections::IMap<std::shared_ptr<Sorter::Models::Job>, 
                            void>> __results;
            
        }; /* class MultiPatternMatcher */ 
    
    } /* namespace Services */
} /* namespace Sorter */ 

#endif /* SORTER_SERVICES_MULTIPATTERNMATCHER_H */

