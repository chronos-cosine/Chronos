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

#include "File/Spooler.h"
#include "Pdf/Splitter/Services/SplittingMachine.h"

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
              
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths) 
              : m_is_running(false),
                m_is_stopping(false),
                m_notifier(nullptr) {
                init(t_paths, std::chrono::seconds(5));
            }
            
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths,
                                 const std::shared_ptr<Notifier::INotifier>& t_notifier)
              : m_is_running(false),
                m_is_stopping(false),
                m_notifier(t_notifier) {
                notify("SplittingMachine::SplittingMachine()");
                
                init(t_paths, std::chrono::seconds(5));
            }
            
            void 
            SplittingMachine::init(const std::vector<fs::path>& t_paths,
                          const std::chrono::seconds& t_sleep_time) {
                notify("SplittingMachine::init()");
                
                initialise_producers(t_paths, t_sleep_time);
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
            SplittingMachine::create_producer_threads() {
                notify("SplittingMachine::create_producer_threads()");

                for (auto& producer: m_job_producers) {
                    std::thread thread(&Processors::IProcessor::start, producer);
                    thread.detach();
                    m_job_producer_threads.push_back(std::move(thread));
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

                m_job_producer_threads.clear();

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