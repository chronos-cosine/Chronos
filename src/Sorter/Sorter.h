/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 05 November 2018, 6:31 PM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Settings/SpoolerSettings.h"

#include <mutex>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    class Sorter {
        Sorter(const Sorter&) = delete;
    public:
        virtual ~Sorter() = default;
        Sorter(const Settings::SpoolerSettings& spooler_settings);
        virtual bool start();
        virtual bool stop();
    private:
        void stop_spoolers();
        void start_spoolers();
        void create_spoolers(const Settings::SpoolerSettings& spooler_settings);
    private:
        std::mutex __mutex;
        bool __is_running;
        std::shared_ptr<Collections::ICollection<Job>> job_paths;
        std::vector<std::shared_ptr<File::Spooler<Job>>> __spoolers;
        std::vector<std::thread> __spooler_threads;
    }; /* class Sorter */

} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

