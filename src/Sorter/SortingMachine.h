/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 26 October 2018, 8:57 AM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ConcurrentQueue.h"
#include "Processors/FileSpooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Sorter/StartupSettings.h"
#include "Sorter/Sorter.h"

#include <string>
#include <vector>
#include <thread>

namespace Sorter {
    
    class SortingMachine {
    private:
        StartupSettings& __startup_settings;
        Collections::ConcurrentQueue<boost::filesystem::path> __job_queue;
        std::vector<Processors::FileSpooler> __file_spoolers;
        std::vector<std::thread> __file_spooler_threads;
        std::vector<Sorter> __sorters;
        std::vector<std::thread> __sorter_threads;
        PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter> __pattern_matcher;
    public:
        SortingMachine(const SortingMachine&) = delete;
        virtual ~SortingMachine();
        SortingMachine(StartupSettings& startup_settings);
        
        void start();
        void stop();
    };
}


#endif /* SORTER_SORTINGMACHINE_H */

