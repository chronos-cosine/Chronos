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
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_jobs,
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_results,
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
                : m_jobs(t_jobs), 
                  m_results(t_results), 
                  m_notifier(nullptr) {
            init(t_data_context);
        }
        
        SortingProcess::SortingProcess(
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_jobs,
                    const std::shared_ptr<Collections::ICollection<std::shared_ptr<Sorter::Models::Job>>>& t_results,
                    const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                    const std::shared_ptr<Notifier::INotifier>& t_notifier) 
                : m_jobs(t_jobs), 
                  m_results(t_results), 
                  m_notifier(t_notifier) {
            notify("SortingProcess::SortingProcess()");
            init(t_data_context);
        }
        
        void 
        SortingProcess::init(const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) {
            notify("SortingProcess::init()");
            
            std::vector<std::shared_ptr<Sorter::Models::Pattern>> patterns;
            
            for (auto& pair: t_data_context->patterns) {
                patterns.push_back(pair.second);
            }
            
            m_data_providers.push_back(std::make_shared<DataProviders::MultiPatternMatcher>(patterns, m_notifier));
            m_data_validators.push_back(std::make_shared<DataValidators::NotDataValidator>(t_data_context, m_notifier));
            m_data_validators.push_back(std::make_shared<DataValidators::OrDataValidator>(t_data_context, m_notifier));
            m_data_validators.push_back(std::make_shared<DataValidators::AndDataValidator>(t_data_context, m_notifier));
        }
        
        bool 
        SortingProcess::process() {
            notify("SortingProcess::process()");

            auto job = std::move(m_jobs->pop());
            populate(job);
            validate(job);
            remove_invalid(job);
            save(job);
            
            return true;
        }
        
        void 
        SortingProcess::populate(const std::shared_ptr<Sorter::Models::Job>& t_job) {
            notify("SortingProcess::populate()");
            
            for (auto& data_provider: m_data_providers) {
                data_provider->process(t_job);
            }
        }
        
        void 
        SortingProcess::validate(const std::shared_ptr<Sorter::Models::Job>& t_job) {
            notify("SortingProcess::validate()");
            
            for (auto& data_validator: m_data_validators) {
                data_validator->process(t_job);
            }
        }
        
        void 
        SortingProcess::remove_invalid(const std::shared_ptr<Sorter::Models::Job>& t_job) {
            notify("SortingProcess::remove_invalid()");
            
            std::set<std::shared_ptr<Sorter::Models::Result>> to_erase;
            for (auto& result: t_job->results) {
                if (!result->passed) {
                    to_erase.insert(result);
                }
            }
            for (auto& result: to_erase) {
                t_job->results.erase(result);
            }
        }
        
        void 
        SortingProcess::save(const std::shared_ptr<Sorter::Models::Job>& t_job) {
            notify("SortingProcess::save()");
            
            std::string name = "./results/" + std::to_string(t_job->id) + ".result";
            std::ofstream result_output(name);
           
            File::JsonDataWriter<Sorter::Models::Job>::write(result_output, *t_job);
        }
        
        void 
        SortingProcess::notify(const std::string& t_message) {
            if (nullptr != m_notifier) {
                m_notifier->notify(t_message);
            }
        }

    } /* namespace Services */
} /* namespace Sorter */