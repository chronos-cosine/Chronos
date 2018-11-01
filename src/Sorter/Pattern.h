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

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

namespace Sorter {
    
    struct Pattern {
        unsigned long long id;
        std::string value;
        BooleanOperator boolean_operator;
        unsigned long long bin_id;

        std::string::const_iterator begin() const;
        std::string::const_iterator end() const;
        bool operator<(const Pattern& rhs) const;
        bool operator==(const Pattern& rhs) const;
        bool operator!=(const Pattern& rhs) const;
        Pattern& operator<<(const std::vector<std::string>& rhs);
        Pattern& operator<<(const boost::property_tree::ptree& rhs);
        
        friend std::ostream& operator<<(std::ostream& lhs, const Pattern& rhs);
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Pattern& rhs);
        
    }; /* struct Pattern */
    
} /* namespace Sorter */

#endif /* SORTER_PATTERN_H */

