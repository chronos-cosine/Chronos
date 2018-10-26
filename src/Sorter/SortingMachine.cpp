/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/SortingMachine.h"

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 26 October 2018, 8:57 AM
 */

#include "Processors/FileSpooler.h"

#include <boost/filesystem/path.hpp>
#include <thread>

namespace Sorter {
    
    SortingMachine::~SortingMachine() { }
    
    SortingMachine::SortingMachine(StartupSettings& startup_settings)
        : __startup_settings(startup_settings) {
        for (const std::string& directory: startup_settings.get_job_file_directories()) {
            __file_spoolers.push_back(Processors::FileSpooler(directory,
                    startup_settings.get_sorter_trigger_extension(),
                    startup_settings.get_sorter_busy_extension(),
                    __job_queue,
                    startup_settings.get_notifier(),
                    30));
        }
    }
    
    void 
    SortingMachine::start() {
        for (auto& file_spooler: __file_spoolers) {
            __file_spooler_threads.push_back(
                std::thread(&Processors::FileSpooler::start, 
                    std::ref(file_spooler)));
            __file_spooler_threads.back().detach();
        }
    }
   
    void 
    SortingMachine::stop() {
        for (auto& file_spooler: __file_spoolers) {
            file_spooler.stop();
        }
    }
}


