/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/Bin.h"

/* 
 * File:   Bin.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 12:19 PM
 */


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

namespace Sorter {

    Bin::Bin(const unsigned long long& id, 
             const std::string& name,
             const unsigned long long& parent_id)
       : __id(id), __name(name), __parent_id(parent_id), 
         __parent(nullptr) { }
    
    Bin::Bin(const Bin& orig)
       : __id(orig.__id), __name(orig.__name), 
         __parent_id(orig.__parent_id), __parent(orig.__parent) { }
    
    Bin::Bin(Bin&& move)
    { }
    
    Bin::~Bin() { }
    
    //member functions
    const std::shared_ptr<Bin>&
    Bin::get_parent() const {
        return __parent;
    }
    
    void
    Bin::set_parent(const std::shared_ptr<Bin>& parent) {
        std::lock_guard<std::mutex> lock(__mutex);
        __parent = parent;
    }
    
    const unsigned long long& 
    Bin::get_id() const {
        return __id;
    }
    
    const unsigned long long& 
    Bin::get_parent_id() const {
        return __parent_id;
    }
    
    const std::string& 
    Bin::get_name() const {
        return __name;
    }

    //operators
    Bin& 
    Bin::operator=(Bin&& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        __id = std::move(rhs.__id);
        __name = std::move(rhs.__name);
        __parent_id = std::move(rhs.__parent_id);
        __parent = std::move(rhs.__parent);
        
        return *this;
    }
    
    Bin& 
    Bin::operator=(const Bin& rhs) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = rhs.__id;
        __name = rhs.__name;
        __parent_id = rhs.__parent_id;
        __parent = rhs.__parent;
        
        return *this;
    }
    
    bool 
    Bin::operator==(const Bin& rhs) const {
        return __id == rhs.__id;
    }
    
    bool 
    Bin::operator!=(const Bin& rhs) const {
        return __id != rhs.__id;
    }
    
    bool 
    Bin::operator<(const Bin& rhs) const {
        if (__parent_id == rhs.__parent_id) {
            return __id < rhs.__id;
        }
        else {
            return __parent_id < rhs.__parent_id;
        }
    }
    
    bool 
    Bin::operator>(const Bin& rhs) const {
        if (__parent_id == rhs.__parent_id) {
            return __id > rhs.__id;
        }
        else {
            return __parent_id > rhs.__parent_id;
        }
    }
    
    //friend operators
    bool 
    operator<(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return false;
        }
        if (nullptr == lhs) { 
            return true;
        }
        if (nullptr == rhs) {
            return false;
        } 
        
        return *lhs < *rhs;
    }
    
    bool 
    operator>(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return false;
        }
        if (nullptr == lhs) { 
            return false;
        }
        if (nullptr == rhs) {
            return true;
        } 
        
        return *lhs > *rhs;
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Bin& rhs) {
        lhs.put("Id", rhs.__id);
        lhs.put("Name", rhs.__name);
        if (nullptr == rhs.__parent) { 
            lhs.put("Parent", "null");
        } else {
            boost::property_tree::ptree parent;
            parent << *rhs.__parent;
            lhs.add_child("Parent", parent);
        }
                
        return lhs;
    }
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Bin& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs;

        boost::property_tree::write_json(lhs, ptree);
        return lhs;
    }
    
} /* namespace Sorter */