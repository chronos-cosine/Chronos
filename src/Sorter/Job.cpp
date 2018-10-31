/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.cpp
 * Author: user
 * 
 * Created on 31 October 2018, 7:07 AM
 */

#include "Job.h"

#include "File/JsonDataWriter.h"

namespace Sorter {
    
    bool 
    Job::operator<(const Job& rhs) {
        
    }
    
    bool 
    Job::operator==(const Job& rhs) {
        
    }
    
    bool 
    Job::operator!=(const Job& rhs) {
        
    }
    
    Bin& Job::operator<<(const boost::property_tree::ptree& rhs) {
        
    }

    std::ostream& 
    operator<<(std::ostream& lhs, const Job& rhs) {
        File::JsonDataWriter::write<Bin>(lhs, rhs);
        return lhs;
    }
    
    friend boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Job& rhs) {
        
    }

    
    std::ostream& operator<<(std::ostream& lhs, const Bin& rhs) {
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Bin& rhs) {
        lhs.put("id", rhs.id);
        lhs.put("name", rhs.name);
        lhs.put("parent_id", rhs.parent_id);
        
} /* namespace Sorter */
