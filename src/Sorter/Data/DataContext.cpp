/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataContext.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 16 November 2018, 8:47 PM
 */

#include "DataContext.h"

#include <exception>

namespace Sorter {
    namespace Data {
        
        void 
        DataContext::link_bin_patterns() {
            for(auto& pattern: patterns) {
                if (bins.find(pattern.second->bin_id) == bins.end()) {
                    throw std::runtime_error(
                        "DataContext::link_bin_patterns() pattern.bin_id not found in bins");
                }
                
                bins[pattern.second->bin_id]->patterns.insert(pattern.second);
                pattern.second->bin = bins[pattern.second->bin_id];
            }
        }
        
        void 
        DataContext::clear() {
            bins.clear();
            patterns.clear();
        }
          
    } /* namespace Data */
} /* namespace Sorter */
