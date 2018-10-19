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
    
    bool 
    operator<(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
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
    operator>(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
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
    
    bool 
    operator==(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return true;
        }
        if (nullptr == lhs
            || nullptr == rhs) { 
            return false;
        } 
        
        return *lhs == *rhs;
    }
    
    bool 
    operator!=(const std::shared_ptr<Job>& lhs, const std::shared_ptr<Job>& rhs) {
        return !(lhs == rhs);
    }
    
    std::ostream& 
    operator<<(std::ostream& lhs, const Job& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs;

        boost::property_tree::write_json(lhs, ptree);
        return lhs;
    }
    
} /* namespace Sorter */