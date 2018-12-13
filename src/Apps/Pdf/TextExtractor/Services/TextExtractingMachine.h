/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextExtractingMachine.h
 * Author: user
 *
 * Created on 11 December 2018, 11:10 AM
 */

#ifndef PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTINGMACHINE_H
#define PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTINGMACHINE_H


#include "Collections/ICollection.h"
#include "Notifier/INotifier.h"
#include "Apps/Pdf/TextExtractor/Models/Job.h"
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
    namespace TextExtractor { 
        namespace Services { 
             
            class TextExtractingMachine : public Processors::ProducerConsumerBase {
            public:
                virtual ~TextExtractingMachine() = default;
                TextExtractingMachine(const std::vector<fs::path>& t_paths,
                                 const std::chrono::seconds& t_sleep_time,
                                 const unsigned short& t_consumer_count,
                                 const std::string& t_output_directory); 
                TextExtractingMachine(const std::vector<fs::path>& t_paths,
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
                std::shared_ptr<Collections::ICollection<std::shared_ptr<Pdf::TextExtractor::Models::Job>>> m_jobs;
                std::string m_output_directory;
            };
            
        } /* namespace Models */
    } /* namespace TextExtractor */
} /* namespace Pdf */
 
#endif /* PDF_TEXTEXTRACTOR_SERVICES_TEXTEXTRACTINGMACHINE_H */

