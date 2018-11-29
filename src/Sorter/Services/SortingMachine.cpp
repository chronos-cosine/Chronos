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
#include "Sorter/Services/SortingMachine.h"
#include "Sorter/Services/SortingProcess.h"
#include "Sorter/Models/Job.h"

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
            m_is_running(false),
            m_is_stopping(false),
            m_notifier(nullptr) {
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
            m_is_running(false),
            m_is_stopping(false),
            m_notifier(t_notifier) {
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
                    m_jobs, m_results, m_data_context, m_notifier));
            }
        }

        void 
        SortingMachine::create_producer_threads() {
            notify("SortingMachine::create_producer_threads()");
            
            for (auto& producer: m_job_producers) {
                std::thread thread(&Processors::IProcessor::start, producer);
                thread.detach();
                m_job_producer_threads.push_back(std::move(thread));
            }
        }

        void 
        SortingMachine::create_consumer_threads() {
            notify("SortingMachine::create_consumer_threads()");
            
            for (auto& consumer: m_job_consumers) {
                std::thread thread(&Processors::IProcessor::start, consumer);
                thread.detach();
                m_job_consumer_threads.push_back(std::move(thread));
            }
        }

        void 
        SortingMachine::stop_producer_threads() {
            notify("SortingMachine::stop_producer_threads()");
            
            for (auto& producer: m_job_producers) {
                producer->stop();
            }
        }

        void 
        SortingMachine::stop_consumer_threads() {
            notify("SortingMachine::stop_consumer_threads()");
            
            for (auto& consumer: m_job_consumers) {
                consumer->stop();
            }
        }
        
        bool 
        SortingMachine::get_is_running() const noexcept {
            return m_is_running && !m_is_stopping;
        }

        bool 
        SortingMachine::start() {
            notify("SortingMachine::start()");
            
            std::lock_guard<std::mutex> lock(m_mutex);
            
            if (m_is_running || m_is_stopping) { 
                return false;
            }

            m_is_running = true;
            create_producer_threads();
            create_consumer_threads();

            return true;
        }

        bool 
        SortingMachine::stop() {
            notify("SortingMachine::stop()");
            
            std::lock_guard<std::mutex> lock(m_mutex);

            if (!m_is_running || m_is_stopping) {
                return false;
            }

            m_is_stopping = true;
            stop_producer_threads();
            stop_consumer_threads();

            m_job_producer_threads.clear();
            m_job_consumer_threads.clear();

            m_is_stopping = false;
            return true;
        }
        
        void 
        SortingMachine::notify(const std::string& t_message) {
            if (nullptr != m_notifier) {
                m_notifier->notify(t_message);
            }
        }
    
    } /* namespace Services */
} /* namespace Sorter */
