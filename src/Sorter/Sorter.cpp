/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 05 November 2018, 7:52 PM
 */

#include "Sorter.h"

#include <memory>
#include <map>
#include <set>

namespace Sorter {
    
    Sorter::Sorter(std::shared_ptr<std::map<unsigned long long, Bin>> bins,
               std::shared_ptr<std::map<unsigned long long, Pattern>> patterns,
               std::shared_ptr<std::map<unsigned long long, std::map<BooleanOperator, 
                        std::set<Pattern>>>> bin_patterns,
               std::shared_ptr<Collections::ICollection<Job>> jobs) 
        : __bins(bins), __patterns(patterns), __bin_patterns(bin_patterns),
          __jobs(jobs) {
    }
    
    bool
    Sorter::process() {
        Job job = std::move(__jobs->pop());
        
        return true;
    }
    
} /* namespace Sorter */ 
