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
#include "Apps/Pdf/Splitter/Models/Job.h"
#include "Processors/IProcessor.h"
#include "Processors/ProducerConsumerBase.h"

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
             
            class SplittingMachine : public Processors::ProducerConsumerBase {
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
            private:
                void init(const std::vector<fs::path>& t_paths,
                          const std::chrono::seconds& t_sleep_time,
                          const unsigned short& t_consumer_count);
                void initialise_producers(const std::vector<fs::path>& t_paths,
                        const std::chrono::seconds& t_sleep_time);
                void initialise_consumers(const unsigned short& t_consumer_count);
            private:
                std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::Splitter::Models::Job>>> m_jobs;
                std::string m_output_directory;
            };
            
        } /* namespace Models */
    } /* namespace Splitter */
} /* namespace Pdf */

#endif /* PDF_SPLITTER_SERVICES_SPLITTINGMACHINE_H */

