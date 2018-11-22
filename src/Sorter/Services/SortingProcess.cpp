/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingProcess.cpp
 * Author: user
 * 
 * Created on 22 November 2018, 9:29 AM
 */

#include "Sorter/Data/DataContext.h"
#include "Sorter/Services/DataProviders/MultiPatternMatcher.h"
#include "SortingProcess.h"

namespace Sorter {
    namespace Services {
        
        SortingProcess::SortingProcess(const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& jobs,
                           const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& results,
                           const std::shared_ptr<Sorter::Data::DataContext>& dc) 
                : __jobs(jobs), __results(results) {
            std::vector<std::shared_ptr<Sorter::Models::Pattern>> patterns;
            for (auto& pair: dc->patterns) {
                patterns.push_back(pair.second);
            }
            
            __data_providers.push_back(std::make_shared<MultiPatternMatcher>(std::move(patterns)));
            //__data_validators.push_back(std::make_shared<NOT>());
            //__data_validators.push_back(std::make_shared<OR>());
            //__data_validators.push_back(std::make_shared<AND>());
        }
        
        bool 
        SortingProcess::process() {
            auto job = __jobs->pop();
            
            // populate data to validate
            for (auto& data_provider: __data_providers) {
                data_provider->process(job.ptr());
            }
            
            // validate the data
            for (auto& data_validator: __data_validators) {
                if (!data_validator->process(job.ptr())) {
                    break;
                }
            }
            
            return true;
        }

    } /* namespace Services */
} /* namespace Sorter */