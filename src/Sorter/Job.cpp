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

#include "Job.h"

namespace Sorter {

    Job::Job(const unsigned long long& id, const char* document) 
        : __id(id), __document(document) { }

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
    
    //friend operators
    std::ostream& 
    operator<<(std::ostream& lhs, const Job& rhs) {
        lhs << "{\"Id\":\"" << rhs.__id
            << "\",\"Document\":\"" << rhs.__document
            << "\"}";
        
        return lhs;
    } 
    
} /* namespace Sorter */