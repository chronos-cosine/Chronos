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

#include "Sorter.h"
#include "Pattern.h"

#include <boost/signals2.hpp>
#include <iostream>

namespace Sorter {
    
    template <typename T>
    std::set<T*>
    Sorter::map_values_to_set(const std::map<unsigned long long, T*> map) {
        std::set<T*> set;
        for (const auto& pair: map) {
            set.insert(pair.second);
        }
        
        return set;
    }

    Sorter::Sorter(char* pattern_file, char* bin_file) 
                : __bins(__bin_file_reader.read(bin_file)),
                  __patterns(__pattern_file_reader.read(pattern_file)),
                  __pattern_matching_machine(map_values_to_set(__patterns)) {
        link_pattern_bin();
        __completed_functor.__sorter = this;
        __match_found_functor.__sorter = this;
        __pattern_matching_machine.completed().connect(__completed_functor);
        __pattern_matching_machine.match_found().connect(__match_found_functor);
    }
    
    Sorter::~Sorter() { 
        __memory_management.free_bins(__bins);
        __memory_management.free_patterns(__patterns);
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

} /* namespace Sorter */
