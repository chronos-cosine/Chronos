/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ConcurrentQueue.h"
#include "Processors/FileSpooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Bin.h"
#include "Sorter/PatternBinLinker.h"
#include "Sorter/StartupSettings.h"

#include <memory>
#include <vector>
#include <string>
#include <set>

namespace Sorter {

    class SortingMachine {
    private:
        StartupSettings& __startup_settings;
        std::vector<std::shared_ptr<Processors::FileSpooler>> __file_spoolers;
        Collections::ConcurrentQueue<boost::filesystem::path> __job_queue;
        std::vector<std::shared_ptr<Sorter>> __sorters;
        PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter> __pattern_matching_machine;
    public:
        SortingMachine(StartupSettings& startup_settings);
        virtual ~SortingMachine();
        
        void start();
        void stop();
        void reset_folder_files(const std::string& folder);
    public:
        SortingMachine(const Sorter&) = delete;
        SortingMachine& operator=(const Sorter&) = delete;
        SortingMachine(const Sorter&&) = delete;
        SortingMachine& operator=(const Sorter&&) = delete;
    };  
    
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

