/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SplittingMachine.cpp
 * Author: user
 * 
 * Created on 04 December 2018, 10:47 AM
 */

#include "Collections/Concurrent/Queue.h"
#include "File/Spooler.h"
#include "Pdf/Splitter/Services/SplittingMachine.h"
#include "Pdf/Splitter/Services/PdfSplitter.h"

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
              
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths,
                                               const std::chrono::seconds& t_sleep_time,
                                               const unsigned short& t_consumer_count) 
              : m_jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Pdf::Splitter::Models::Job>>>()),
                m_is_running(false),
                m_is_stopping(false),
                m_notifier(nullptr) {
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths,
                                const std::chrono::seconds& t_sleep_time,
                                const unsigned short& t_consumer_count,
                                const std::shared_ptr<Notifier::INotifier>& t_notifier)
              : m_jobs(std::make_shared<
                Collections::Concurrent::Queue<std::shared_ptr<Pdf::Splitter::Models::Job>>>()),
                m_is_running(false),
                m_is_stopping(false),
                m_notifier(t_notifier) {
                notify("SplittingMachine::SplittingMachine()");
                
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            void 
            SplittingMachine::init(const std::vector<fs::path>& t_paths,
                          const std::chrono::seconds& t_sleep_time,
                          const unsigned short& t_consumer_count) {
                notify("SplittingMachine::init()");
                
                initialise_producers(t_paths, t_sleep_time);
                initialise_consumers(t_consumer_count);
            }
            
            void 
            SplittingMachine::initialise_producers(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time) {
                notify("SplittingMachine::initialise_producers()");
                
                for (auto& path: t_paths) {
                    auto producer = std::make_shared<File::Spooler<Pdf::Splitter::Models::Job>>(path, 
                            ".sjob", ".sdone", t_sleep_time, m_jobs);
                    m_job_producers.push_back(std::move(producer));
                }
            }
            
            void 
            SplittingMachine::initialise_consumers(const unsigned short& t_consumer_count) {
                notify("SplittingMachine::initialise_consumers()");

                for (unsigned short i = 0; i < t_consumer_count; ++i) {
                    m_job_consumers.push_back(std::make_shared<PdfSplitter>(m_jobs,
                            m_notifier));
                }
            }

            void 
            SplittingMachine::create_producer_threads() {
                notify("SplittingMachine::create_producer_threads()");

                for (auto& producer: m_job_producers) {
                    std::thread thread(&Processors::IProcessor::start, producer);
                    thread.detach();
                    m_job_producer_threads.push_back(std::move(thread));
                }
            }
                 
            void 
            SplittingMachine::create_consumer_threads() {
                notify("SplittingMachine::create_consumer_threads()");

                for (auto& consumer: m_job_consumers) {
                    std::thread thread(&Processors::IProcessor::start, consumer);
                    thread.detach();
                    m_job_consumer_threads.push_back(std::move(thread));
                }
            }
            
            bool 
            SplittingMachine::start() {
                notify("SplittingMachine::start()");

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
            SplittingMachine::stop() {
                notify("SplittingMachine::stop()");

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
            SplittingMachine::stop_producer_threads() {
                notify("SplittingMachine::stop_producer_threads()");

                for (auto& producer: m_job_producers) {
                    producer->stop();
                }
            }
            
            void 
            SplittingMachine::stop_consumer_threads() {
                notify("SplittingMachine::stop_consumer_threads()");

                for (auto& consumer: m_job_consumers) {
                    consumer->stop();
                }
            }
            
            bool 
            SplittingMachine::get_is_running() const noexcept {
                return m_is_running && !m_is_stopping;
            }
           
            void 
            SplittingMachine::notify(const std::string& t_message) {
                if (nullptr != m_notifier) {
                    m_notifier->notify(t_message);
                }
            }
            
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */