/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 9:17 AM
 */

#include "Sorter/Pattern.h" 
#include "PatternMatcher/IPattern.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>

namespace Sorter {

    //constructors
    Pattern::Pattern(const unsigned long long& id, 
                     const char* value,
                     const unsigned long long& bin_id)
        : PatternMatcher::IPattern(value), 
          __id(id), __bin_id(bin_id), __bin(nullptr) { }

    Pattern::Pattern(const unsigned long long& id, 
                     const std::string& value,
                     const unsigned long long& bin_id)
        : PatternMatcher::IPattern(value), 
          __id(id), __bin_id(bin_id), __bin(nullptr) { }

    Pattern::Pattern(const Pattern& orig)
        : PatternMatcher::IPattern(orig), 
          __id(orig.__id), __bin_id(orig.__bin_id), __bin(orig.__bin) { }

    Pattern::~Pattern() { }

    //member functions
    const unsigned long long& 
    Pattern::get_id() const {
        return __id;
    }
    
    const unsigned long long& 
    Pattern::get_bin_id() const {
        return __bin_id;
    }
    
    Bin* 
    Pattern::get_bin() const {
        return __bin;
    }
    
    void 
    Pattern::set_bin(Bin* bin) {
        std::lock_guard<std::mutex> lock(__mutex);
        __bin = bin;
    }

    //operators
    Pattern& 
    Pattern::operator=(const Pattern& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = rhs.__id;
        __bin_id = rhs.__bin_id;
        __bin = rhs.__bin;
        __value = rhs.__value;
        
        return *this;
    }
        
    bool 
    Pattern::operator==(const Pattern& rhs) const {
        return __id == rhs.__id;
    }

    bool 
    Pattern::operator!=(const Pattern& rhs) const {
        return __id != rhs.__id;
    }

    bool 
    Pattern::operator<(const Pattern& rhs) const {
        return __id < rhs.__id;
    }

    bool 
    Pattern::operator>(const Pattern& rhs) const {
        return __id > rhs.__id;
    }
    
    //friend operators
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Pattern& rhs) {
        lhs.put("Id", rhs.__id);
        lhs.put("Value", rhs.__value);
        lhs.put("BinId", rhs.__bin_id);
        
        if (nullptr == rhs.__bin) {
            lhs.put("Bin", "null");
        }
        else {
            boost::property_tree::ptree bin;
            bin << *rhs.__bin;
            lhs.add_child("Bin", bin);
        }
        
        return lhs;
    }    

} /* namespace Sorter */
