/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 04 November 2018, 8:06 PM
 */
#include "Sorter/SortingMachine.h"

#include "Collections/ConcurrentQueue.h"
#include "File/DataReader.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings/SorterSettings.h"

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace Sorter {
    
    SortingMachine::SortingMachine(const Settings::SorterSettings& sorter_settings) 
      : __bins(std::make_shared<std::map<unsigned long long, Bin>>()),
        __patterns(std::make_shared<std::map<unsigned long long, Pattern>>()),
        __bin_patterns(std::make_shared<std::map<unsigned long long, std::map<BooleanOperator, std::set<Pattern>>>>()),
        __jobs(std::make_shared<Collections::ConcurrentQueue<std::string>>()),
        __job_spooler(std::make_shared<JobSpooler>(__jobs, sorter_settings.spooler_settings)) {
        init(sorter_settings);
    }
     
    void 
    SortingMachine::init(const Settings::SorterSettings& sorter_settings) {
        init_bins(sorter_settings.bin_settings);
        init_patterns(sorter_settings.pattern_settings);
        init_pattern_matcher();
        
        __job_spooler->start();
    }
    
    void 
    SortingMachine::init_bins(const Settings::BinSettings& bin_settings) {
        auto bins = File::DataReader<Bin>::read(bin_settings.filename, bin_settings.file_type);
        for (const auto& bin: *bins) {
            __bins[bin.id] = std::move(bin);
        }
    }
    
    void 
    SortingMachine::init_patterns(const Settings::PatternSettings& pattern_settings) {
        auto patterns = File::DataReader<Pattern>::read(pattern_settings.filename, pattern_settings.file_type);
        for (const auto& pattern: *patterns) {
            __bin_patterns[pattern.bin_id][pattern.boolean_operator].insert(pattern);
            __patterns[pattern.id] = std::move(pattern);
        }
    }
    
    void 
    SortingMachine::init_pattern_matcher() {
        std::vector<Pattern> patterns;
        for (const auto& pair: __patterns) {
            patterns.push_back(pair.second);
        }
        __pattern_matcher = std::make_shared<PatternMatcher::PatternMatchingMachine<Job, Pattern, SortingMachine>>(patterns);
    }
    
} /* namespace Sorter */