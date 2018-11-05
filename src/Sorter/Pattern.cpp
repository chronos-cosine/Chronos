/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Pattern.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 30 October 2018, 10:52 PM
 */

#include "Pattern.h"
#include "File/JsonDataWriter.h"

#include <exception>
#include <iostream>

namespace Sorter {

    std::string::const_iterator  
    Pattern::begin() const {
        return value.begin();
    }
    
    std::string::const_iterator  
    Pattern::end() const {
        return value.end();
    }
    
    bool 
    Pattern::operator<(const Pattern& rhs) const {
        if (bin_id < rhs.bin_id) {
            return true;
        }
        
        if (boolean_operator < rhs.boolean_operator) {
            return true;
        }
        
        return id < rhs.id;
    }
    
    bool 
    Pattern::operator!=(const Pattern& rhs) const {
        return !(*this == rhs);
    }
    bool 
    Pattern::operator==(const Pattern& rhs) const {
        return id == rhs.id;
    }

    Pattern& 
    Pattern::operator<<(const std::vector<std::string>& rhs) {
        if (rhs.size() != 4) { 
            throw std::runtime_error("Pattern operator<< requires size() == 4");
        }
        
        id = std::stoull(rhs[0]);
        value = rhs[1];
        bin_id = std::stoull(rhs[2]);
        boolean_operator = (BooleanOperator)std::stoi(rhs[3]);
        
        return *this;
    }
    
    Pattern&  
    Pattern::operator<<(const boost::property_tree::ptree& rhs) {
        id = rhs.get<unsigned long long>("id");
        value = rhs.get<std::string>("value");
        boolean_operator = (BooleanOperator)rhs.get<unsigned short>("boolean_operator");
        bin_id = rhs.get<unsigned long long>("bin_id");
        
        return *this;
    }

    //friend operators
    bool
    operator<(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return false;
        } else if (nullptr == lhs) {
            return true;
        } else if (nullptr == rhs) {
            return false;
        }
        
        return *lhs < *rhs;
    }
    
    bool
    operator==(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return true;
        } else if (nullptr == lhs || nullptr == rhs) {
            return false;
        }
        
        return *lhs == *rhs;
    }
    
    bool
    operator!=(const std::shared_ptr<Pattern>& lhs, const std::shared_ptr<Pattern>& rhs) {
        return !(lhs == rhs);
    }

    std::ostream& 
    operator<<(std::ostream& lhs, const Pattern& rhs) {
        File::JsonDataWriter<Pattern>::write(lhs, rhs);
        return lhs;
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Pattern& rhs) {
        lhs.put("id", rhs.id);
        lhs.put("value", rhs.value);
        lhs.put("boolean_operator", rhs.boolean_operator);
        lhs.put("bin_id", rhs.bin_id);
        
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
    
    template <>
    struct hash<std::shared_ptr<Sorter::Pattern>> {
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Pattern>& pattern) const {
            if (nullptr == pattern)
            {
                return 0;
            }
            return std::hash<unsigned long long>{}(pattern->id);
        }
    };
} /* namespace std */

