/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 16 November 2018, 8:01 PM
 */

#ifndef SORTER_MODELS_PATTERN_H
#define SORTER_MODELS_PATTERN_H

#include "Sorter/Models/BooleanOperator.h"

#include <boost/property_tree/ptree.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Sorter {
    namespace Models {
        struct Bin;
        
        struct Pattern {
            unsigned long long id;
            std::string value;
            BooleanOperator boolean_operator;
            unsigned long long bin_id;
            
            std::shared_ptr<Bin> bin;
            
            std::string::const_iterator begin() const;
            std::string::const_iterator end() const;
            
            bool operator==(const Pattern& rhs) const noexcept;
            bool operator!=(const Pattern& rhs) const noexcept;
            bool operator<(const Pattern& rhs) const noexcept;
            Pattern& operator=(const Pattern& rhs);
            Pattern& operator<<(const std::vector<std::string>& rhs);
            
            boost::property_tree::ptree& 
            operator>>(boost::property_tree::ptree& lhs) const;
            
        }; /* struct Pattern */
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_PATTERN_H */

