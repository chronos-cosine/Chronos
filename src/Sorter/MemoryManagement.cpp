/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemoryManagement.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 2:10 PM
 */

#include "Sorter/MemoryManagement.h"
#include <mutex>

namespace Sorter {
    
    MemoryManagement::MemoryManagement() { }

    MemoryManagement::~MemoryManagement() { }
    
    void 
    MemoryManagement::free_patterns(std::map<unsigned long long, Pattern*>& patterns) {
        std::lock_guard<std::mutex> lock(__mutex);
        for (auto& pair: patterns) {
            delete pair.second;
        }
        patterns.clear();
    }
    
    void 
    MemoryManagement::free_bins(std::map<unsigned long long, Bin*>& bins) {
        std::lock_guard<std::mutex> lock(__mutex);
        for (auto& pair: bins) {
            delete pair.second;
        }
        bins.clear();
    } 
} /* namespace Sorter */