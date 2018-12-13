/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 11:14 AM
 */

#include "Collections/Concurrent/Queue.h"
#include "File/Spooler.h"
#include "Apps/Sorter/Services/SortingMachine.h"
#include "Apps/Sorter/Services/SortingProcess.h"
#include "Apps/Sorter/Models/Job.h"

#include <chrono>
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {
    
        SortingMachine::SortingMachine(const std::vector<fs::path>& t_paths, 
                           const std::chrono::seconds& t_sleep_time,
                           const unsigned short& t_consumer_count,
                           const std::shared_ptr<Sorter::Data::DataContext>& t_data_context) 
          : m_jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            m_results(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            m_data_context(t_data_context),
            Processors::ProducerConsumerBase() {
            init(t_paths, t_sleep_time, t_consumer_count);
        }
        
        SortingMachine::SortingMachine(const std::vector<fs::path>& t_paths, 
                           const std::chrono::seconds& t_sleep_time,
                           const unsigned short& t_consumer_count,
                           const std::shared_ptr<Sorter::Data::DataContext>& t_data_context,
                           const std::shared_ptr<Notifier::INotifier>& t_notifier) 
          : m_jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            m_results(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            m_data_context(t_data_context),
            Processors::ProducerConsumerBase(t_notifier) {
            notify("SortingMachine::SortingMachine()");
            
            init(t_paths, t_sleep_time, t_consumer_count);
        }
        
        void 
        SortingMachine::init(const std::vector<fs::path>& t_paths,
                             const std::chrono::seconds& t_sleep_time,
                             const unsigned short& t_consumer_count) {
            notify("SortingMachine::init()");
            
            initialise_producers(t_paths, t_sleep_time);
            initialise_consumers(t_consumer_count);
        }

        void 
        SortingMachine::initialise_producers(const std::vector<fs::path>& t_paths, 
                                        const std::chrono::seconds& t_sleep_time) {
            notify("SortingMachine::initialise_producers()");
            
            for (auto& path: t_paths) {
                auto producer = std::make_shared<File::Spooler<Sorter::Models::Job>>(path, 
                        ".sjob", ".sdone", t_sleep_time, m_jobs);
                m_job_producers.push_back(std::move(producer));
            }
        }

        void 
        SortingMachine::initialise_consumers(const unsigned short& t_consumer_count) {
            notify("SortingMachine::initialise_consumers()");
            
            for (unsigned short i = 0; i < t_consumer_count; ++i) {
                m_job_consumers.push_back(std::make_shared<SortingProcess>(
                    m_jobs, m_results, m_data_context, get_notifier()));
            }
        }
    
    } /* namespace Services */
} /* namespace Sorter */
