/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.h
 * Author: user
 *
 * Created on 30 October 2018, 8:24 AM
 */

#ifndef SORTER_PATTERN_H
#define SORTER_PATTERN_H

#include "Sorter/BooleanOperator.h"

#include <string>
#include <vector>

namespace Sorter {
    
    struct Pattern {
        unsigned long long id;
        std::string value;
        BooleanOperator boolean_operator;
        unsigned long long bin_id;

        bool operator<(const Pattern& rhs);
        bool operator==(const Pattern& rhs);
        bool operator!=(const Pattern& rhs);
        Pattern& operator<<(const std::vector<std::string>& rhs);
        std::string::const_iterator begin();
        std::string::const_iterator end();
        
        friend std::ostream& operator<<(std::ostream& lhs, const Pattern& rhs);
    }; /* struct Pattern */
    
} /* namespace Sorter */

#endif /* SORTER_PATTERN_H */

