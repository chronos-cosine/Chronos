/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextExtractingMachine.cpp
 * Author: user
 * 
 * Created on 11 December 2018, 11:11 AM
 */

#include "Collections/Concurrent/Queue.h"
#include "File/Spooler.h"
#include "Pdf/TextExtractor/Services/TextExtractingMachine.h"
#include "Pdf/TextExtractor/Services/TextExtractor.h"

namespace Pdf {
    namespace TextExtractor { 
        namespace Services { 
            
            TextExtractingMachine::TextExtractingMachine(const std::vector<fs::path>& t_paths,
                                               const std::chrono::seconds& t_sleep_time,
                                               const unsigned short& t_consumer_count,
                                               const std::string& t_output_directory) 
              : m_jobs(std::make_shared<
                    Collections::Concurrent::Queue<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>()),
                m_is_running(false),
                m_is_stopping(false),
                m_output_directory(t_output_directory),
                m_notifier(nullptr) {
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            TextExtractingMachine::TextExtractingMachine(const std::vector<fs::path>& t_paths,
                                const std::chrono::seconds& t_sleep_time,
                                const unsigned short& t_consumer_count,
                                const std::string& t_output_directory,
                                const std::shared_ptr<Notifier::INotifier>& t_notifier)
              : m_jobs(std::make_shared<
                    Collections::Concurrent::Queue<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>()),
                m_is_running(false),
                m_is_stopping(false),
                m_output_directory(t_output_directory),
                m_notifier(t_notifier) {
                notify("TextExtractingMachine::TextExtractingMachine()");
                
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            void 
            TextExtractingMachine::init(const std::vector<fs::path>& t_paths,
                          const std::chrono::seconds& t_sleep_time,
                          const unsigned short& t_consumer_count) {
                notify("TextExtractingMachine::init()");
                
                initialise_producers(t_paths, t_sleep_time);
                initialise_consumers(t_consumer_count);
            }
            
            void 
            TextExtractingMachine::initialise_producers(const std::vector<fs::path>& t_paths,
                    const std::chrono::seconds& t_sleep_time) {
                notify("TextExtractingMachine::initialise_producers()");
                
                for (auto& path: t_paths) {
                    auto producer = std::make_shared<File::Spooler<Pdf::TextExtractor::Models::Job>>(path, 
                            ".sjob", ".sdone", t_sleep_time, m_jobs);
                    m_job_producers.push_back(std::move(producer));
                }
            }
            
            void 
            TextExtractingMachine::initialise_consumers(const unsigned short& t_consumer_count) {
                notify("TextExtractingMachine::initialise_consumers()");

                for (unsigned short i = 0; i < t_consumer_count; ++i) {
//                    m_job_consumers.push_back(std::make_shared<TextExtractor>(m_jobs,
//                            m_output_directory,
//                            m_notifier));
                }
            }

            void 
            TextExtractingMachine::create_producer_threads() {
                notify("TextExtractingMachine::create_producer_threads()");

                for (auto& producer: m_job_producers) {
                    std::thread thread(&Processors::IProcessor::start, producer);
                    thread.detach();
                    m_job_producer_threads.push_back(std::move(thread));
                }
            }
                 
            void 
            TextExtractingMachine::create_consumer_threads() {
                notify("TextExtractingMachine::create_consumer_threads()");

                for (auto& consumer: m_job_consumers) {
                    std::thread thread(&Processors::IProcessor::start, consumer);
                    thread.detach();
                    m_job_consumer_threads.push_back(std::move(thread));
                }
            }
            
            bool 
            TextExtractingMachine::start() {
                notify("TextExtractingMachine::start()");

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
            TextExtractingMachine::stop() {
                notify("TextExtractingMachine::stop()");

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
            TextExtractingMachine::stop_producer_threads() {
                notify("TextExtractingMachine::stop_producer_threads()");

                for (auto& producer: m_job_producers) {
                    producer->stop();
                }
            }
            
            void 
            TextExtractingMachine::stop_consumer_threads() {
                notify("TextExtractingMachine::stop_consumer_threads()");

                for (auto& consumer: m_job_consumers) {
                    consumer->stop();
                }
            }
            
            bool 
            TextExtractingMachine::get_is_running() const noexcept {
                return m_is_running && !m_is_stopping;
            }
           
            void 
            TextExtractingMachine::notify(const std::string& t_message) {
                if (nullptr != m_notifier) {
                    m_notifier->notify(t_message);
                }
            }
            
        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */