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

#include "SortingMachine.h"

#include "Collections/ConcurrentQueue.h"
#include "File/DataReader.h"
#include "File/Spooler.h"
#include "Sorter/Settings/SpoolerSettings.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace Sorter {
    
    SortingMachine::SortingMachine(const Settings::SorterSettings& sorter_settings) 
      : jobs(std::make_shared<Collections::ConcurrentQueue<Job>>()),
        __is_running(false),
        __bins(std::make_shared<std::map<unsigned long long, Bin>>()),
        __patterns(std::make_shared<std::map<unsigned long long, Pattern>>()),  
        __bin_patterns(std::make_shared<std::map<unsigned long long, std::map<BooleanOperator, 
                        std::set<Pattern>>>>()) {
        create_bins(sorter_settings.bin_settings);
        create_patterns(sorter_settings.pattern_settings);
        create_spoolers(sorter_settings.spooler_settings);
        create_sorters(sorter_settings);
    }
    
    void 
    SortingMachine::create_bins(const Settings::BinSettings& bin_settings) {
        auto bins = File::DataReader<Bin>::read(bin_settings.filename, 
                        bin_settings.file_type);
        
        for (const auto& bin: *bins) {
            (*__bins)[bin.id] = std::move(bin);
        }
    }
    
    void 
    SortingMachine::create_patterns(const Settings::PatternSettings& pattern_settings) {
        auto patterns = File::DataReader<Pattern>::read(pattern_settings.filename, 
                        pattern_settings.file_type);
        
        for (const auto& pattern: *patterns) {
            (*__bin_patterns)[pattern.bin_id][pattern.boolean_operator]
                    .insert(pattern);
            (*__patterns)[pattern.id] = std::move(pattern);
        }
    }
    
    void 
    SortingMachine::create_spoolers(const Settings::SpoolerSettings& spooler_settings) {
        for (const auto& directory: spooler_settings.directories) {
            __spoolers.push_back(
                std::make_shared<File::Spooler<Job>>(
                    directory,
                    spooler_settings.trigger_extension,
                    spooler_settings.busy_extension,
                    std::chrono::seconds(5),
                    jobs));
        }
    }
    
    void 
    SortingMachine::create_sorters(const Settings::SorterSettings& sorter_settings) {
        for (unsigned short i = 0; i < sorter_settings.sorter_instances; ++i) {
            __sorters.push_back(
                std::make_shared<Sorter>());
        }
    }
    
    bool 
    SortingMachine::start() {
        std::lock_guard<std::mutex> lock(__mutex);
        
        if (!__is_running) {
            start_spoolers();
            start_sorters();
            __is_running = true;
            return true;
        }
        
        return false;
    }
    
    bool 
    SortingMachine::stop() {
        std::lock_guard<std::mutex> lock(__mutex);
         
        if (__is_running) {
            stop_spoolers();
            stop_sorters();
            __is_running = false;
            return true;
        }
        
        return false;
    }
    
    void 
    SortingMachine::stop_spoolers() {
        for (const auto& spooler: __spoolers) {
            spooler->stop();
        }
        __spooler_threads.clear();
    }
    
    void 
    SortingMachine::start_spoolers() {
        for (const auto& spooler: __spoolers) {
            std::thread thread(&File::Spooler<Job>::start, spooler);
            thread.detach();
            __spooler_threads.push_back(std::move(thread));
        }
    }
    
    void 
    SortingMachine::stop_sorters() {
        for (const auto& sorter: __sorters) {
            sorter->stop();
        }
        __sorter_threads.clear();
    }
    
    void 
    SortingMachine::start_sorters() {
        for (const auto& sorter: __sorters) {
            std::thread thread(&Sorter::start, sorter);
            thread.detach();
            __sorter_threads.push_back(std::move(thread));
        }
    }
    
} /* namespace Sorter */
