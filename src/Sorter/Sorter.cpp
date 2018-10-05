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

namespace Sorter {

    Sorter::Sorter(char* pattern_file, char* bin_file) 
        : __bins(__bin_file_reader.read(bin_file)),
          __patterns(__pattern_file_reader.read(pattern_file)) {
        link_pattern_bin();
        __pattern_matching_machine(__patterns);
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

} /* namespace Sorter */