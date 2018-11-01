/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.h
 * Author: user
 *
 * Created on 01 November 2018, 9:27 AM
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
        std::set<Pattern>* pattern_matches;
        std::set<Bin>* bin_matches;
        
        friend std::ostream& operator<<(std::ostream& lhs, const Result& rhs);
        
    }; /* struct Result */
    
} /* namespace Sorter */

#endif /* SORTER_RESULT_H */

