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
                m_output_directory(t_output_directory),
                Processors::ProducerConsumerBase() {
                init(t_paths, t_sleep_time, t_consumer_count);
            }
            
            TextExtractingMachine::TextExtractingMachine(const std::vector<fs::path>& t_paths,
                                const std::chrono::seconds& t_sleep_time,
                                const unsigned short& t_consumer_count,
                                const std::string& t_output_directory,
                                const std::shared_ptr<Notifier::INotifier>& t_notifier)
              : m_jobs(std::make_shared<
                    Collections::Concurrent::Queue<std::shared_ptr<Pdf::TextExtractor::Models::Job>>>()),
                m_output_directory(t_output_directory),
                Processors::ProducerConsumerBase(t_notifier) {
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

        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */