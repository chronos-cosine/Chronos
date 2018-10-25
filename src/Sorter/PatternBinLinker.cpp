/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/PatternBinLinker.h"

/* 
 * File:   PatternBinLinker.cpp
 * Author: user
 * 
 * Created on 11 October 2018, 12:08 PM
 */

#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"

#include <set>
#include <map>
#include <mutex>

namespace Sorter {

    PatternBinLinker::~PatternBinLinker() { }
    
    PatternBinLinker::PatternBinLinker() { }

    void 
    PatternBinLinker::link(const std::map<unsigned long long, std::shared_ptr<Pattern>>& patterns, 
                           const std::map<unsigned long long, std::shared_ptr<Bin>>& bins) {
        std::lock_guard<std::mutex> lock(__mutex);
        for (auto& pair: patterns) {
            auto bin = bins.find(pair.second->get_bin_id());
            if (bin != bins.end()) {
                pair.second->set_bin(bin->second);
                bin->second->get_patterns().insert(pair.second);
            }
        }
    }

} /* namespace Sorter */