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

#include "SortingProcess.h"
#include "MultiPatternMatcher.h"

namespace Sorter {
    namespace Services {
        
        SortingProcess::SortingProcess(const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& j,
                           const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& r) 
            : jobs(j), results(r) {
            // data_providers.push_back(std::make_shared<MultiPatternMatcher>(vector<sharedPtr<pattern>));
        }
        
        bool 
        SortingProcess::process() {
            auto job = jobs->pop();
            
            // populate data to validate
            for (auto& data_provider: data_providers) {
                data_provider->process(job.ptr());
            }
            
            // validate the data
            for (auto& data_validator: data_validators) {
                if (!data_validator->process(job.ptr())) {
                    break;
                }
            }
            
            return true;
        }

    } /* namespace Services */
} /* namespace Sorter */