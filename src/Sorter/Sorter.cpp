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

    Sorter::Sorter(char* pattern_file, char* bin_file) 
        : __bins(__bin_file_reader.read(bin_file)),
          __patterns(__pattern_file_reader.read(pattern_file)),
          __pattern_matching_machine(__patterns) 
    { 
        link_pattern_bin();  
        __pattern_matching_machine.completed().connect(
                boost::bind(
                    &Sorter::pattern_match_completed, 
                    this, 
                    _1));
        __pattern_matching_machine.match_found().connect(
                boost::bind(
                    &Sorter::pattern_match_found, 
                    this, 
                    _1));
    }

    Sorter::~Sorter() { 
        __memory_management.free_bins(__bins);
        __memory_management.free_patterns(__patterns);
    }

    void 
    Sorter::link_pattern_bin() {
        for (auto& p: __patterns) {
            Pattern* pattern = dynamic_cast<Pattern*>(p);
            for (auto& bin: __bins) {
                if (bin->get_id() == pattern->get_bin_id())
                {
                    pattern->set_bin(bin);
                    continue;
                }
            }
        }
    }
        
    void 
    Sorter::pattern_match_completed(void* sender, 
             const unsigned long long& total_matches,
             PatternMatcher::IPattern* input)
    {
        std::cout << "completed" << std::endl;
    }
    
    void 
    Sorter::pattern_match_found(void* sender , 
             const unsigned long long& position,
             PatternMatcher::IPattern* input ,
             const std::set<PatternMatcher::IPattern*>& patterns)
    {
        std::cout << "match found" << std::endl;
    }

} /* namespace Sorter */