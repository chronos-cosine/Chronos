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

#include "Collections/ConcurrentQueue.h"
#include "Core/Helpers.h"
#include "Processors/FileSpooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Sorter/StartupSettings.h"
#include "Sorter/Sorter.h"

#include <boost/filesystem/path.hpp>
#include <thread>

namespace Sorter {
    
    SortingMachine::~SortingMachine() { }
    
    SortingMachine::SortingMachine(StartupSettings& startup_settings)
        : __startup_settings(startup_settings),
          __pattern_matcher(Core::Helpers::get_value_set(__startup_settings.get_patterns())) {
        for (const std::string& directory: startup_settings.get_job_file_directories()) {
            __file_spoolers.push_back(Processors::FileSpooler(directory,
                    startup_settings.get_sorter_trigger_extension(),
                    startup_settings.get_sorter_busy_extension(),
                    __job_queue,
                    startup_settings.get_notifier(),
                    30));
        }
        
        for (unsigned short i = 0; i < startup_settings.get_sorter_count(); ++i) {
            __sorters.push_back(Sorter(__pattern_matcher,
                                       __job_queue, 30,
                                       startup_settings));
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
        
        for (auto& sorter: __sorters) {
            __sorter_threads.push_back(
                std::thread(&Sorter::start,
                    std::ref(sorter)));
            __sorter_threads.back().detach();
        }
    }
   
    void 
    SortingMachine::stop() {
        for (auto& file_spooler: __file_spoolers) {
            file_spooler.stop();
        }
        for (auto& sorter: __sorters) {
            sorter.stop();
        }
    }
}


