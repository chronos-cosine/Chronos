/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/Job.h"

/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 8:52 AM
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

namespace Sorter {

    Job::Job(const unsigned long long& id, const std::string& document, const std::string& filename) 
       : __id(id), __document(document), __filename(filename) { }

    Job::~Job() { }
    
    Job::Job(const Job& other) 
       : __id(other.__id), __document(other.__document), __filename(other.__filename) { }
        
    Job::Job(Job&& other) 
       : __id(std::move(other.__id)), __document(std::move(other.__document)), 
         __filename(std::move(other.__filename)) { }
    
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

    std::string::const_iterator 
    Job::begin() const {
        return __document.begin();
    }
    
    std::string::const_iterator 
    Job::end() const {
        return __document.end();
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
    
    Job& 
    Job::operator=(Job&& job) {
        std::lock_guard<std::mutex> lock(__mutex);
        __id = std::move(job.__id);
        __document = std::move(job.__document);
        __filename = std::move(job.__filename);
        
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
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Job& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs;

        boost::property_tree::write_json(lhs, ptree);
        return lhs;
    }
    
} /* namespace Sorter */