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

namespace Sorter {
    
    MemoryManagement::MemoryManagement() 
    { }

    MemoryManagement::~MemoryManagement() 
    { }
    
    void 
    MemoryManagement::free_patterns(std::set<PatternMatcher::IPattern*>& patterns)
    {
        for (auto* pattern: patterns)
        {
            delete pattern;
        }
        patterns.clear();
    }
    
    void 
    MemoryManagement::free_bins(std::set<Bin*>& bins)
    {
        for (auto* bin: bins)
        {
            delete bin;
        }
        bins.clear();
    } 
} /* namespace Sorter */