/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 8:24 AM
 */

#include "Pattern.h"

#include <exception>
#include <iostream>

namespace Sorter {

    bool 
    Pattern::operator<(const Pattern& rhs) {
        if (bin_id < rhs.bin_id) {
            return true;
        }
        
        if (boolean_operator < rhs.boolean_operator) {
            return true;
        }
        
        return id < rhs.id;
    }

    bool 
    Pattern::operator==(const Pattern& rhs) {
        return id == rhs.id;
    }

    bool 
    Pattern::operator!=(const Pattern& rhs) {
        return !(*this == rhs);
    }
    
    Pattern& 
    Pattern::operator<<(const std::vector<std::string>& rhs) {
        if (rhs.size() != 4) { 
            throw std::runtime_error("Pattern operator<< requires size() == 4");
        }
        
        id = std::stoull(rhs[0]);
        value = rhs[1];
        boolean_operator = (BooleanOperator)std::stoi(rhs[2]);
        bin_id = std::stoull(rhs[3]);
        
        return *this;
    }
    
    std::string::const_iterator  
    Pattern::begin() {
        return value.begin();
    }
    
    std::string::const_iterator  
    Pattern::end() {
        return value.end();
    }

    std::ostream& operator<<(std::ostream& lhs, const Pattern& rhs) {
        lhs << "{\"Id\": \"" << rhs.id
            << "\", \"Value\": \"" << rhs.value
            << "\", \"BooleanOperator\": \"" << rhs.boolean_operator
            << "\", \"Bin_Id\": \"" << rhs.bin_id
            << "\"}";
        
        return lhs;
    }
        
} /* namespace Sorter */

namespace std {
    
    template <>
    struct hash<Sorter::Pattern> {
        std::size_t 
        operator()(const Sorter::Pattern& pattern) const {
            return std::hash<unsigned long long>{}(pattern.id);
        }
    };
} /* namespace std */

