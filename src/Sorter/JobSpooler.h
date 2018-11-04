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

#include <mutex>
#include <string>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    class JobSpooler : public Processors::ProcessorBase {
        JobSpooler(const JobSpooler&) = delete;
    public:
        virtual ~JobSpooler() = default;
        JobSpooler(const std::shared_ptr<Collections::ICollection<std::string>>& jobs,
                   const Settings::SpoolerSettings& settings);
        
        virtual void start();
        virtual void stop();
    protected:
        virtual bool process();
    private:
        std::mutex __mutex;
        std::vector<std::shared_ptr<File::Spooler>> __spoolers;
        std::vector<std::thread> __spooler_threads;
    };

} /* namespace Sorter */
    
#endif /* SORTER_JOBSPOOLER_H */

