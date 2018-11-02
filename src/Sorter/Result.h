/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Result.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 01 November 2018, 10:52 PM
 */

#ifndef SORTER_RESULT_H
#define SORTER_RESULT_H

#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
 
#include <set>

namespace Sorter {
    
    struct Result {
        Job* job;
        std::map<unsigned long long, std::set<Pattern>>* pattern_matches;
        std::set<Bin>* bin_matches;
        
        friend std::ostream& operator<<(std::ostream& lhs, const Result& rhs);
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Result& rhs);
        
    }; /* struct Result */
    
} /* namespace Sorter */

#endif /* SORTER_RESULT_H */

