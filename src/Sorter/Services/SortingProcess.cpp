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
#include "DataValidators/NotDataValidator.h"
#include "DataValidators/AndDataValidator.h"
#include "DataValidators/OrDataValidator.h"

namespace Sorter {
    namespace Services {
        
        SortingProcess::SortingProcess(
                    const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& jobs,
                    const std::shared_ptr<Collections::ICollection<Sorter::Models::Job>>& results,
                    const std::shared_ptr<Sorter::Data::DataContext>& dc) 
                : __jobs(jobs), __results(results) {
            std::vector<std::shared_ptr<Sorter::Models::Pattern>> patterns;
            for (auto& pair: dc->patterns) {
                patterns.push_back(pair.second);
            }
            
            __data_providers.push_back(std::make_shared<DataProviders::MultiPatternMatcher>(std::move(patterns)));
            __data_validators.push_back(std::make_shared<DataValidators::NotDataValidator>(dc));
            __data_validators.push_back(std::make_shared<DataValidators::OrDataValidator>(dc));
            __data_validators.push_back(std::make_shared<DataValidators::AndDataValidator>(dc));
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
                data_validator->process(job.ptr());
            }
            
            // erase false matches
            std::set<std::shared_ptr<Sorter::Models::Result>> to_erase;
            for (auto& result: job.results) {
                if (!result->passed) {
                    to_erase.insert(result);
                }
            }
            for (auto& result: to_erase) {
                job.results.erase(result);
            }
            
            return true;
        }

    } /* namespace Services */
} /* namespace Sorter */