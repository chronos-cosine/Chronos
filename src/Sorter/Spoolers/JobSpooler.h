/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JobSpooler.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 6:34 PM
 */

#ifndef SORTER_JOBSPOOLER_H
#define SORTER_JOBSPOOLER_H

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "Processors/ProcessorBase.h"
#include "Settings/SpoolerSettings.h"
#include "Sorter/Job.h"
#include "JobSpoolerFileReader.h"

#include <mutex>
#include <string>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    namespace Spoolers {
        
        class JobSpooler : public Processors::ProcessorBase {
            JobSpooler(const JobSpooler&) = delete;
        public:
            virtual ~JobSpooler() = default;
            JobSpooler(const std::shared_ptr<Collections::ICollection<Job>>& jobs,
                       const Settings::SpoolerSettings& settings);

            virtual void start();
            virtual void stop();
        protected:
            virtual bool process();
        private:
            std::mutex __mutex;
            std::shared_ptr<Collections::ICollection<std::string>> __jobs_paths;
            std::shared_ptr<Collections::ICollection<Job>> __jobs;
            std::vector<std::shared_ptr<File::Spooler>> __spoolers;
            std::vector<std::shared_ptr<JobSpoolerFileReader>> __job_file_readers;
            std::vector<std::thread> __spooler_threads;
            std::vector<std::thread> __job_file_reader_threads;
        }; /* class JobSpooler */
        
    } /* namespace Spoolers */
    
} /* namespace Sorter */
    
#endif /* SORTER_JOBSPOOLER_H */

