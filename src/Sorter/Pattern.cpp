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

#include "Sorter/BooleanOperator.h"
#include "Sorter/Pattern.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <sstream>
#include <string>

namespace Sorter {

    //constructors
    Pattern::Pattern(const unsigned long long& id, 
                     const char* value,
                     const unsigned long long& bin_id,
                     const BooleanOperator& boolean_operator)
        : __value(value), 
          __id(id), __bin_id(bin_id), __bin(nullptr), __boolean_operator(boolean_operator) { }

    Pattern::Pattern(const unsigned long long& id, 
                     const std::string& value,
                     const unsigned long long& bin_id,
                     const BooleanOperator& boolean_operator)
        : __value(value), 
          __id(id), __bin_id(bin_id), __bin(nullptr), __boolean_operator(boolean_operator) { }

    Pattern::Pattern(const Pattern& orig)
        : __value(orig.__value), 
          __id(orig.__id), __bin_id(orig.__bin_id), __bin(orig.__bin), 
          __boolean_operator(orig.__boolean_operator){ }
    
    Pattern::Pattern(Pattern&& orig)
        : __value(std::move(orig.__value)), 
          __id(std::move(orig.__id)), __bin_id(std::move(orig.__bin_id)), 
          __bin(std::move(orig.__bin)), __boolean_operator(std::move(orig.__boolean_operator)) { }

    Pattern::~Pattern() { }

    //member functions 
    const std::string& 
    Pattern::get_value() const {
        return __value;
    }
    
    std::string::iterator 
    Pattern::begin() {
        return __value.begin();
    }
    
    std::string::const_iterator 
    Pattern::begin() const {
        return __value.begin();
    }
    
    std::string::iterator 
    Pattern::end() {
        return __value.end();
    }
    
    std::string::const_iterator 
    Pattern::end() const {
        return __value.end();
    }
        
    const unsigned long long& 
    Pattern::get_id() const {
        return __id;
    }
    
    const unsigned long long& 
    Pattern::get_bin_id() const {
        return __bin_id;
    }
    
    
    const BooleanOperator& 
    Pattern::get_boolean_operator() const {
        return __boolean_operator;
    }
    
    const std::shared_ptr<Bin> &
    Pattern::get_bin() const {
        return __bin;
    }
    
    void 
    Pattern::set_bin(const std::shared_ptr<Bin>& bin) {
        std::lock_guard<std::mutex> lock(__mutex);
        __bin = bin;
    }

    //operators
    Pattern& 
    Pattern::operator=(Pattern&& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = std::move(rhs.__id);
        __bin_id = std::move(rhs.__bin_id);
        __bin = std::move(rhs.__bin);
        __value = std::move(rhs.__value);
        __boolean_operator = std::move(rhs.__boolean_operator);
        
        return *this;
    }
    
    Pattern& 
    Pattern::operator=(const Pattern& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = rhs.__id;
        __bin_id = rhs.__bin_id;
        __bin = rhs.__bin;
        __value = rhs.__value;
        __boolean_operator = rhs.__boolean_operator;
        
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
        lhs.put("BooleanOperator", rhs.__boolean_operator);
        
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
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Pattern& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs;

        boost::property_tree::write_json(lhs, ptree);
        return lhs;
    }

} /* namespace Sorter */
