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
#include "SortingMachine.h"
#include "SortingProcess.h"
#include "Sorter/Models/Job.h"

#include <chrono>
#include <experimental/filesystem>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    namespace Services {
    
        SortingMachine::SortingMachine(const std::vector<fs::path>& paths, 
                           const std::chrono::seconds& sleep_time,
                           const unsigned short& consumer_count,
                           const std::shared_ptr<Sorter::Data::DataContext>& dc) 
          : jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            results(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            __data_context(dc),
            __is_running(false),
            __is_stopping(false),
            __notifier(nullptr) {
            init(paths, sleep_time, consumer_count);
        }
        
        SortingMachine::SortingMachine(const std::vector<fs::path>& paths, 
                           const std::chrono::seconds& sleep_time,
                           const unsigned short& consumer_count,
                           const std::shared_ptr<Sorter::Data::DataContext>& dc,
                           const std::shared_ptr<Notifier::INotifier> notifier) 
          : jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            results(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Sorter::Models::Job>>>()),
            __data_context(dc),
            __is_running(false),
            __is_stopping(false),
            __notifier(notifier) {
            notify("SortingMachine::SortingMachine()");
            
            init(paths, sleep_time, consumer_count);
        }
        
        void 
        SortingMachine::init(const std::vector<fs::path>& paths,
                             const std::chrono::seconds& sleep_time,
                             const unsigned short& consumer_count) {
            notify("SortingMachine::init()");
            
            initialise_producers(paths, sleep_time);
            initialise_consumers(consumer_count);
        }

        void 
        SortingMachine::initialise_producers(const std::vector<fs::path>& paths, 
                                        const std::chrono::seconds& sleep_time) {
            notify("SortingMachine::initialise_producers()");
            
            for (auto& path: paths) {
                auto producer = std::make_shared<File::Spooler<Sorter::Models::Job>>(path, 
                        ".sjob", ".sdone", sleep_time, jobs);
                job_producers.push_back(std::move(producer));
            }
        }

        void 
        SortingMachine::initialise_consumers(const unsigned short& consumer_count) {
            notify("SortingMachine::initialise_consumers()");
            
            for (unsigned short i = 0; i < consumer_count; ++i) {
                job_consumers.push_back(std::make_shared<SortingProcess>(
                    jobs, results, __data_context));
            }
        }

        void 
        SortingMachine::create_producer_threads() {
            notify("SortingMachine::create_producer_threads()");
            
            for (auto& producer: job_producers) {
                std::thread thread(&Processors::IProcessor::start, producer);
                thread.detach();
                job_producer_threads.push_back(std::move(thread));
            }
        }

        void 
        SortingMachine::create_consumer_threads() {
            notify("SortingMachine::create_consumer_threads()");
            
            for (auto& consumer: job_consumers) {
                std::thread thread(&Processors::IProcessor::start, consumer);
                thread.detach();
                job_consumer_threads.push_back(std::move(thread));
            }
        }

        void 
        SortingMachine::stop_producer_threads() {
            notify("SortingMachine::stop_producer_threads()");
            
            for (auto& producer: job_producers) {
                producer->stop();
            }
        }

        void 
        SortingMachine::stop_consumer_threads() {
            notify("SortingMachine::stop_consumer_threads()");
            
            for (auto& consumer: job_consumers) {
                consumer->stop();
            }
        }
        
        bool 
        SortingMachine::get_is_running() const noexcept {
            return __is_running && !__is_stopping;
        }

        bool 
        SortingMachine::start() {
            std::lock_guard<std::mutex> lock(__mutex);
            notify("SortingMachine::start()");
            
            if (__is_running || __is_stopping) { 
                return false;
            }

            __is_running = true;
            create_producer_threads();
            create_consumer_threads();

            return true;
        }

        bool 
        SortingMachine::stop() {
            std::lock_guard<std::mutex> lock(__mutex);
            notify("SortingMachine::stop()");

            if (!__is_running || __is_stopping) {
                return false;
            }

            __is_stopping = true;
            stop_producer_threads();
            stop_consumer_threads();

            job_producer_threads.clear();
            job_consumer_threads.clear();

            __is_stopping = false;
            return true;
        }
        
        void 
        SortingMachine::notify(const std::string& message) {
            if (nullptr != __notifier) {
                __notifier->notify(message);
            }
        }
    
    } /* namespace Services */
} /* namespace Sorter */
