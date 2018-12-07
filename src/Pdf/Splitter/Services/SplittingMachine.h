/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SplittingMachine.h
 * Author: user
 *
 * Created on 04 December 2018, 10:47 AM
 */

#ifndef PDF_SPLITTER_SERVICES_SPLITTINGMACHINE_H
#define PDF_SPLITTER_SERVICES_SPLITTINGMACHINE_H

#include "Collections/ICollection.h"
#include "Notifier/INotifier.h"
#include "Pdf/Splitter/Models/Job.h"
#include "Processors/IProcessor.h"

#include <experimental/filesystem>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
             
            class SplittingMachine {
            public:
                virtual ~SplittingMachine() = default;
                SplittingMachine(const std::vector<fs::path>& t_paths,
                                 const std::chrono::seconds& t_sleep_time,
                                 const unsigned short& t_consumer_count,
                                 const std::string& t_output_directory); 
                SplittingMachine(const std::vector<fs::path>& t_paths,
                                 const std::chrono::seconds& t_sleep_time,
                                 const unsigned short& t_consumer_count,
                                 const std::string& t_output_directory,
                                 const std::shared_ptr<Notifier::INotifier>& t_notifier); 
            public:
                bool start();
                bool stop();
                bool get_is_running() const noexcept;
            private:
                void init(const std::vector<fs::path>& t_paths,
                          const std::chrono::seconds& t_sleep_time,
                          const unsigned short& t_consumer_count);
                void initialise_producers(const std::vector<fs::path>& t_paths,
                        const std::chrono::seconds& t_sleep_time);
                void initialise_consumers(const unsigned short& t_consumer_count);
                void create_producer_threads();
                void create_consumer_threads();
                void stop_producer_threads();
                void stop_consumer_threads();
                void notify(const std::string& t_message);
            private:
                std::shared_ptr<Notifier::INotifier> m_notifier;
                std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>> m_jobs;
                std::vector<std::shared_ptr<Processors::IProcessor>> m_job_producers;
                std::vector<std::shared_ptr<Processors::IProcessor>> m_job_consumers;
                std::vector<std::thread> m_job_producer_threads;
                std::vector<std::thread> m_job_consumer_threads;
                std::mutex m_mutex;
                bool m_is_running;
                bool m_is_stopping;
                std::string m_output_directory;
            };
            
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */

#endif /* PDF_SPLITTER_SERVICES_SPLITTINGMACHINE_H */

