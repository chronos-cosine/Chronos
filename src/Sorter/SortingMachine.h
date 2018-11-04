/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 04 November 2018, 8:06 PM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ICollection.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"
#include "Sorter/Job.h"
#include "Sorter/JobSpooler.h"
#include "Sorter/Pattern.h"
#include "Sorter/Sorter.h"
#include "Sorter/Settings/SorterSettings.h"

#include <map>
#include <set>
#include <string>

namespace Sorter {
    
    class SortingMachine {
        SortingMachine(const SortingMachine&) = delete;
    public:
        virtual ~SortingMachine() = default;
        SortingMachine(const Settings::SorterSettings& sorter_settings);
    private:
        void init(const Settings::SorterSettings& sorter_settings);
        void init_bins(const Settings::BinSettings& bin_settings);
        void init_patterns(const Settings::PatternSettings& pattern_settings);
        void init_pattern_matcher();
    private:
        std::shared_ptr<std::map<unsigned long long, Bin>> __bins;
        std::shared_ptr<std::map<unsigned long long, Pattern>> __patterns;
        std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, std::set<Pattern>>>> __bin_patterns;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, SortingMachine>> __pattern_matcher;
        std::shared_ptr<Collections::ICollection<Job>> __jobs;
        std::shared_ptr<JobSpooler> __job_spooler;
        std::shared_ptr<Sorter> __sorter;
        
    }; /* class SortingMachine */
    
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

