/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 1:13 PM
 */

#include "SortingMachine.h"
#include "File/DataReader.h"
#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings.h"

#include <exception>
#include <map>
#include <set>

namespace Sorter {
    
    SortingMachine::~SortingMachine() {
    }
    
    SortingMachine::SortingMachine(Settings* settings) 
        : __settings(settings) {
        initialise();
    }
    
    void 
    SortingMachine::initialise() {
        std::vector<Bin> bins = 
                std::move(File::DataReader::read<Bin>(__settings->bins_path, __settings->bins_file_type));
        std::vector<Pattern> patterns = 
                std::move(File::DataReader::read<Pattern>(__settings->patterns_path, __settings->patterns_file_type));
        
        for (Bin& bin: bins) {
            unsigned long long bin_id = bin.id;
            __bins[bin_id] = std::move(bin);
        }
        for (Pattern& pattern: patterns) {
            unsigned long long bin_id = pattern.bin_id;
            unsigned long long pattern_id = pattern.id;
            __patterns[pattern_id] = std::move(pattern);
            if (bin_id > 0) {
                __bin_patterns[bin_id].insert(&__patterns[pattern.id]);
            }
        }
    }
    
} /* namespace Sorter */

