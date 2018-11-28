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

#include "File/JsonDataWriter.h"
#include "Sorter/Data/DataContext.h"
#include "Sorter/Models/Job.h"
#include "Sorter/Services/DataProviders/MultiPatternMatcher.h"
#include "Sorter/Services/DataValidators/NotDataValidator.h"
#include "Sorter/Services/DataValidators/AndDataValidator.h"
#include "Sorter/Services/DataValidators/OrDataValidator.h"
#include "Sorter/Services/SortingProcess.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {
        
        SortingProcess::SortingProcess(
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& jobs,
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& results,
                    const std::shared_ptr<Sorter::Data::DataContext>& dc) 
                : __jobs(jobs), 
                  __results(results), 
                  __notifier(nullptr) {
        }
        
        SortingProcess::SortingProcess(
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& jobs,
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& results,
                    const std::shared_ptr<Sorter::Data::DataContext>& dc,
                    const std::shared_ptr<Notifier::INotifier>& notifier) 
                : __jobs(jobs), 
                  __results(results), 
                  __notifier(notifier) {
            notify("SortingProcess::SortingProcess()");
        }
        
        void 
        SortingProcess::init(const std::shared_ptr<Sorter::Data::DataContext>& dc) {
            notify("SortingProcess::init()");
            
            std::vector<std::shared_ptr<Sorter::Models::Pattern>> patterns;
            
            for (auto& pair: dc->patterns) {
                patterns.push_back(pair.second);
            }
            
            __data_providers.push_back(std::make_shared<DataProviders::MultiPatternMatcher>(patterns));
            __data_validators.push_back(std::make_shared<DataValidators::NotDataValidator>(dc));
            __data_validators.push_back(std::make_shared<DataValidators::OrDataValidator>(dc));
            __data_validators.push_back(std::make_shared<DataValidators::AndDataValidator>(dc));
        }
        
        bool 
        SortingProcess::process() {
            notify("SortingProcess::process()");

            auto job = std::move(__jobs->pop());
            populate(job);
            validate(job);
            remove_invalid(job);
            save(job);
            
            return true;
        }
        
        void 
        SortingProcess::populate(const std::shared_ptr<Sorter::Models::Job>& job) {
            notify("SortingProcess::populate()");
            
            for (auto& data_provider: __data_providers) {
                data_provider->process(job);
            }
        }
        
        void 
        SortingProcess::validate(const std::shared_ptr<Sorter::Models::Job>& job) {
            notify("SortingProcess::validate()");
            
            for (auto& data_validator: __data_validators) {
                data_validator->process(job);
            }
        }
        
        void 
        SortingProcess::remove_invalid(const std::shared_ptr<Sorter::Models::Job>& job) {
            notify("SortingProcess::remove_invalid()");
            
            std::set<std::shared_ptr<Sorter::Models::Result>> to_erase;
            for (auto& result: job->results) {
                if (!result->passed) {
                    to_erase.insert(result);
                }
            }
            for (auto& result: to_erase) {
                job->results.erase(result);
            }
        }
        
        void 
        SortingProcess::save(const std::shared_ptr<Sorter::Models::Job>& job) {
            notify("SortingProcess::save()");
            
            std::string name = "./results/" + std::to_string(job->id) + ".result";
            std::ofstream result_output(name);
           
            File::JsonDataWriter<Sorter::Models::Job>::write(result_output, *job);
        }
        
        void 
        SortingProcess::notify(const std::string& message) const {
            if (nullptr != __notifier) {
                __notifier->notify(message);
            }
        }

    } /* namespace Services */
} /* namespace Sorter */