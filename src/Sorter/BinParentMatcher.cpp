/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/BinParentMatcher.h"

/* 
 * File:   BinParentMatcher.cpp
 * Author: user
 * 
 * Created on 16 October 2018, 9:51 AM
 */

#include "Sorter/Bin.h"
#include <memory>
#include <set>

namespace Sorter {
    
    BinParentMatcher::BinParentMatcher() { }

    BinParentMatcher::~BinParentMatcher() { }
    
    void 
    BinParentMatcher::parents_exist(std::set<std::shared_ptr<Bin>>& bins) {
        std::set<std::shared_ptr<Bin>> bins_temp(bins);
        for (auto& bin: bins_temp) {
            std::shared_ptr<Bin> b = bin;
            do {
                b = b->get_parent();
                if (nullptr != b
                    && bins.find(b) == bins.end()) {
                    bins.erase(bin);
                }
            } while (nullptr != b);
        }
    }

} /* namespace Sorter */


