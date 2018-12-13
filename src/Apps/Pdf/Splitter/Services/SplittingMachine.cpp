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
#include "Apps/Pdf/Splitter/Services/SplittingMachine.h"
#include "Apps/Pdf/Splitter/Services/PdfSplitter.h"

namespace Pdf {
    namespace Splitter { 
        namespace Services { 
              
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths,
                                               const std::chrono::seconds& t_sleep_time,
                                               const unsigned short& t_consumer_count,
                                               const std::string& t_output_directory) 
              : m_jobs(std::make_shared<
                    Collections::Concurrent::Queue<std::shared_ptr<Pdf::Splitter::Models::Job>>>()), 
                Processors::ProducerConsumerBase(),
                m_output_directory(t_output_directory) {
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            SplittingMachine::SplittingMachine(const std::vector<fs::path>& t_paths,
                                const std::chrono::seconds& t_sleep_time,
                                const unsigned short& t_consumer_count,
                                const std::string& t_output_directory,
                                const std::shared_ptr<Notifier::INotifier>& t_notifier)
              : m_jobs(std::make_shared<
                    Collections::Concurrent::Queue<std::shared_ptr<Pdf::Splitter::Models::Job>>>()),
                Processors::ProducerConsumerBase(),
                m_output_directory(t_output_directory) {
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
                            m_output_directory,
                            get_notifier()));
                }
            }
            
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */