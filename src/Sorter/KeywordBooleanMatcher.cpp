/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "KeywordBooleanMatcher.h"

/* 
 * File:   KeywordBooleanMatcher.cpp
 * Author: user
 * 
 * Created on 16 October 2018, 11:23 AM
 */

#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"
#include "Sorter/BooleanOperator.h"

#include <set>
#include <map>
#include <memory>

namespace Sorter {

    KeywordBooleanMatcher::KeywordBooleanMatcher() { }
 

    KeywordBooleanMatcher::~KeywordBooleanMatcher() { }
    
    void 
    KeywordBooleanMatcher::match_boolean(std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& patterns,
                                         std::set<std::shared_ptr<Bin>>& bins) {
        std::set<std::shared_ptr<Bin>> temp_bins(bins);
        for (auto& bin: temp_bins) {
            for (auto& pattern: bin->get_patterns()) {
                if (pattern->get_boolean_operator() == BooleanOperator::NOT) {
                    if (patterns.find(pattern) != patterns.end()) {
                        bins.erase(bin);
                    }
                } else if (pattern->get_boolean_operator() == BooleanOperator::AND) {
                    if (patterns.find(pattern) == patterns.end()) {
                        bins.erase(bin);
                    }
                } else if (pattern->get_boolean_operator() == BooleanOperator::OR) { 
                    break;
                }
            }
        }
    }
    
} /* namespace Sorter */


