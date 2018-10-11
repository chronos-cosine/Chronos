/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 8:52 AM
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Sorter/Job.h"

namespace Sorter {

    Job::Job(const unsigned long long& id, const char* document, const char* filename) 
       : __id(id), __document(document), __filename(filename) { }

    Job::~Job() { }
    
    Job::Job(const Job& other) 
       : __id(other.__id), __document(other.__document), __filename(other.__filename) { }
        
    const unsigned long long& 
    Job::get_id() const
    {
        return __id;
    }
    
    const std::string& 
    Job::get_document() const
    {
        return __document;
    }
    
    const std::string& 
    Job::get_filename() const {
        return __filename;
    }
    
    //operators
    Job& 
    Job::operator=(const Job& job) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = job.__id;
        __document = job.__document;
        __filename = job.__filename;
        
        return *this;
    }
    
    bool 
    Job::operator==(const Job& rhs) const {
        return __id == rhs.__id;
    }
    
    bool 
    Job::operator!=(const Job& rhs) const {
        return __id != rhs.__id;
    }
    
    bool 
    Job::operator<(const Job& rhs) const {
        return __id < rhs.__id;
    }
    
    bool 
    Job::operator>(const Job& rhs) const {
        return __id > rhs.__id;
    }
    
    //friend operators
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Job& rhs) {
        lhs.put("Id", rhs.__id);
        lhs.put("Document", rhs.__document); 
        
        return lhs;
    }
    
} /* namespace Sorter */