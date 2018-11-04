/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JobSpooler.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 04 November 2018, 6:34 PM
 */

#include "Sorter/JobSpooler.h"
#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "Processors/ProcessorBase.h"
#include "Settings/SpoolerSettings.h"

#include <chrono>
#include <mutex>
#include <string>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    JobSpooler::JobSpooler(const std::shared_ptr<Collections::ICollection<std::string>>& jobs,
                           const Settings::SpoolerSettings& settings) {
        for (const auto& directory: settings.directories) {
            std::shared_ptr<File::Spooler> spooler = std::make_shared<File::Spooler>(directory, 
                                  settings.trigger_extension,
                                  settings.busy_extension,
                                  std::chrono::seconds(30),
                                  jobs);
            __spoolers.push_back(std::move(spooler));
        }
    }
    
    bool 
    JobSpooler::process() {
        return false;
    }
    
    void
    JobSpooler::start() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (!get_is_running() && !get_is_stopping()) {
            __spooler_threads.clear();
            
            for (const auto& spooler: __spoolers) {
                std::thread thread(&File::Spooler::start, spooler);
                thread.detach();
                __spooler_threads.push_back(std::move(thread));
            }
        }
        
        Processors::ProcessorBase::start();
    }
    
    void 
    JobSpooler::stop() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (get_is_running() && !get_is_stopping()) {
            Processors::ProcessorBase::set_is_stopping(true);
            for (const auto& spooler: __spoolers) {
                spooler->stop();

                while (spooler->get_is_stopping()
                       || spooler->get_is_running()) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            }

            __spooler_threads.clear();
            Processors::ProcessorBase::stop();
        }
    }

} /* namespace Sorter */

    
