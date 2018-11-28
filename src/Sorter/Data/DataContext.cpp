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

#include "Sorter/Data/DataContext.h"

#include <exception>

namespace Sorter {
    namespace Data {
        
        void 
        DataContext::link_bin_patterns() {
            for(auto& pair: patterns) {
                if (bins.find(pair.second->bin_id) == bins.end()) {
                    throw std::runtime_error(
                        "DataContext::link_bin_patterns() pattern.bin_id not found in bins");
                }
                
                bins[pair.second->bin_id]->patterns[pair.second->boolean_operator]
                                         .insert(pair.second);
                pair.second->bin = bins[pair.second->bin_id];
            }
        }
        
        void 
        DataContext::clear() {
            bins.clear();
            patterns.clear();
        }
          
    } /* namespace Data */
} /* namespace Sorter */
