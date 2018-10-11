/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternBinLinker.cpp
 * Author: user
 * 
 * Created on 11 October 2018, 12:08 PM
 */

#include "Sorter/PatternBinLinker.h"

#include <map>
#include <mutex>

namespace Sorter {

    PatternBinLinker::PatternBinLinker() { }

    PatternBinLinker::~PatternBinLinker() { }
    
    void 
    PatternBinLinker::link(const std::map<unsigned long long, Pattern*>& patterns, 
                           const std::map<unsigned long long, Bin*>& bins) {
        std::lock_guard<std::mutex> lock(__mutex);
        for (auto& pair: patterns) {
            std::map<unsigned long long, Bin*>::const_iterator bin = bins.find(pair.second->get_bin_id());
            if (bin != bins.end()) {
                pair.second->set_bin(bin->second);
            }
        }
    }

} /* namespace Sorter */