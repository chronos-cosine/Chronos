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

#include "Sorter/Pattern.h"
#include "Sorter/Bin.h"
#include "Sorter/BooleanOperator.h"

#include <iostream>
#include <set>
#include <map>
#include <memory>

namespace Sorter {

    KeywordBooleanMatcher::KeywordBooleanMatcher() { }
 

    KeywordBooleanMatcher::~KeywordBooleanMatcher() { }
    
    void 
    KeywordBooleanMatcher::match_boolean(std::map<std::shared_ptr<Pattern>, std::set<unsigned long long>>& patterns,
                                         std::set<std::shared_ptr<Bin>>& bins,
                                         std::map<std::shared_ptr<Bin>, std::set<std::shared_ptr<Pattern>>>& bin_keywords) {
        std::set<std::shared_ptr<Bin>> temp_bins(bins);
        std::cout << "1 KeywordBooleanMatcher::match_boolean" << std::endl;
        for (auto& bin: temp_bins) {
            std::cout << "2 KeywordBooleanMatcher::match_boolean" << std::endl; 
            for (auto& pattern: bin_keywords[bin]) {
                std::cout << "3 KeywordBooleanMatcher::match_boolean" << std::endl;
                if (pattern->get_boolean_operator() == BooleanOperator::NOT) {
                    std::cout << "4 KeywordBooleanMatcher::match_boolean" << std::endl;
                    if (patterns.find(pattern) != patterns.end()) {
                        std::cout << "5 KeywordBooleanMatcher::match_boolean" << std::endl;
                        bins.erase(bin);
                    }
                } else if (pattern->get_boolean_operator() == BooleanOperator::AND) {
                    std::cout << "6 KeywordBooleanMatcher::match_boolean" << std::endl;
                    if (patterns.find(pattern) == patterns.end()) {
                        std::cout << "7 KeywordBooleanMatcher::match_boolean" << std::endl;
                        bins.erase(bin);
                    }
                }
            }
        }
    }
    
} /* namespace Sorter */


