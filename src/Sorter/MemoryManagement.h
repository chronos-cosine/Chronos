/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MemoryManagement.h
 * Author: user
 *
 * Created on 04 October 2018, 2:10 PM
 */

#ifndef SORTER_MEMORYMANAGEMENT_H
#define SORTER_MEMORYMANAGEMENT_H

#include <map>
#include "Sorter/Bin.h"
#include "PatternMatcher/IPattern.h"

namespace Sorter {
    
    class MemoryManagement {
    public:
        MemoryManagement();
        virtual ~MemoryManagement();
        
        void free_patterns(std::map<unsigned long long, PatternMatcher::IPattern*>& patterns);
        void free_bins(std::map<unsigned long long, Bin*>& bins);
    };

} /* namespace Sorter */

#endif /* SORTER_MEMORYMANAGEMENT_H */

