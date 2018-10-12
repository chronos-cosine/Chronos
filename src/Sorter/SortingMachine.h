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

#include "Core/ConcurrentQueue.h"
#include "Core/FileSpooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Bin.h"

#include <vector>

namespace Sorter {

    class SortingMachine { 
    public:
        SortingMachine(const Sorter&) = delete;
        SortingMachine& operator=(const Sorter&) = delete;
    public:
        SortingMachine(const char* pattern_file, const char* bin_file, 
                std::vector<char*> job_paths, unsigned int sorter_count);
        virtual ~SortingMachine();
        
        void start();
        void stop();
    private:
        std::map<unsigned long long, std::shared_ptr<Pattern>> __patterns;
        std::map<unsigned long long, std::shared_ptr<Bin>> __bins;
        Core::ConcurrentQueue<boost::filesystem::path> __job_queue;
        PatternMatcher::PatternMatchingMachine __pattern_matching_machine;
        std::vector<Core::FileSpooler> __file_spoolers;
        std::vector<Sorter> __sorters;
    };  
    
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

