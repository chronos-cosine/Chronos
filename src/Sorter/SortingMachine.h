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

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings/SpoolerSettings.h"
#include "Sorter/Sorter.h"
#include "Settings/SorterSettings.h"

#include <mutex>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    class SortingMachine {
        SortingMachine(const SortingMachine&) = delete;
    public:
        virtual ~SortingMachine() = default;
        SortingMachine(const Settings::SorterSettings& sorter_settings);
        bool start();
        bool stop();
    private:
        void stop_spoolers();
        void start_spoolers();
        void create_spoolers(const Settings::SpoolerSettings& spooler_settings);
        
        void stop_sorters();
        void start_sorters();
        void create_sorters(const Settings::SorterSettings& sorter_settings);
        
        void create_bins(const Settings::BinSettings& bin_settings);
        void create_patterns(const Settings::PatternSettings& pattern_settings);
    private:
        std::mutex __mutex;
        bool __is_running;
        std::shared_ptr<Collections::ICollection<Job>> __jobs;
        std::vector<std::shared_ptr<File::Spooler<Job>>> __spoolers;
        std::vector<std::thread> __spooler_threads;
        std::vector<std::shared_ptr<Sorter>> __sorters;
        std::vector<std::thread> __sorter_threads;
        std::shared_ptr<std::map<unsigned long long, Bin>> __bins;
        std::shared_ptr<std::map<unsigned long long, Pattern>> __patterns;
        std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, 
                        std::set<Pattern>>>> __bin_patterns;
        
    }; /* class Sorter */

} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

