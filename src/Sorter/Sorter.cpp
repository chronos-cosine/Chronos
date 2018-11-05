/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 05 November 2018, 6:31 PM
 */

#include "Sorter.h"

#include "Collections/ConcurrentQueue.h"
#include "File/Spooler.h"
#include "Sorter/Settings/SpoolerSettings.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    Sorter::Sorter(const Settings::SpoolerSettings& spooler_settings) 
      : job_paths(std::make_shared<Collections::ConcurrentQueue<Job>>()) {
        create_spoolers(spooler_settings);
    }
    
    
    bool 
    Sorter::start() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (!__is_running) {
            start_spoolers();
            __is_running = true;
            return true;
        }
        
        return false;
    }
    
    bool 
    Sorter::stop() {
        std::lock_guard<std::mutex> lock(__mutex);
         
        if (__is_running) {
            stop_spoolers(); 
            __is_running = false;
            return true;
        }
        
        return false;
    }
    
    void 
    Sorter::create_spoolers(const Settings::SpoolerSettings& spooler_settings) {
        for (const auto& directory: spooler_settings.directories) {
            __spoolers.push_back(
                std::make_shared<File::Spooler<Job>>(
                    directory,
                    spooler_settings.trigger_extension,
                    spooler_settings.busy_extension,
                    std::chrono::seconds(30),
                    job_paths));
        }
    }
    
    void 
    Sorter::stop_spoolers() {
        for (const auto& spooler: __spoolers) {
            spooler->stop();
        }
        __spooler_threads.clear();
    }
    
    void 
    Sorter::start_spoolers() {
        for (const auto& spooler: __spoolers) {
            std::thread thread(&File::Spooler<Job>::start, spooler);
            thread.detach();
            __spooler_threads.push_back(std::move(thread));
        }
    }
    
} /* namespace Sorter */
