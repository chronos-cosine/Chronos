/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.cpp
 * Author: user
 * 
 * Created on 05 October 2018, 8:53 AM
 */

#include "Core/INotifier.h"
#include "Core/IProcessor.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"

#include <boost/signals2.hpp>
#include <iostream>

namespace Sorter {
    
    #define SORTER_SLEEP_TIME 5
    
    Sorter::Sorter(char* pattern_file, char* bin_file) 
                : Core::IProcessor(SORTER_SLEEP_TIME), __bins(__bin_file_reader.read(bin_file)),
                  __patterns(__pattern_file_reader.read(pattern_file)),
                  __pattern_matching_machine(map_values_to_set(__patterns)) {
        initialise_sorter();
    }
    
    Sorter::Sorter(char* pattern_file, char* bin_file, Core::INotifier* notifier)
                : Core::IProcessor(SORTER_SLEEP_TIME, notifier), __bins(__bin_file_reader.read(bin_file)),
                  __patterns(__pattern_file_reader.read(pattern_file)),
                  __pattern_matching_machine(map_values_to_set(__patterns)) {
        initialise_sorter();
    }
        
    Sorter::~Sorter() { 
        __memory_management.free_bins(__bins);
        __memory_management.free_patterns(__patterns);
    }
    
    void 
    Sorter::initialise_sorter() {
        link_pattern_bin();
        __completed_functor.__sorter = this;
        __match_found_functor.__sorter = this;
        __pattern_matching_machine.completed().connect(__completed_functor);
        __pattern_matching_machine.match_found().connect(__match_found_functor);
    }

    void 
    Sorter::link_pattern_bin() {
        for (auto& p: __patterns) {
            Pattern* pattern = dynamic_cast<Pattern*>(p.second);
            if (__bins.find(pattern->get_bin_id()) != __bins.end()) {
                pattern->set_bin(__bins[pattern->get_bin_id()]);
            }
        }
    }
    
    bool 
    Sorter::process() {
        return false;
    }
    
} /* namespace Sorter */
