/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 10:58 AM
 */

#include "Settings.h"
#include "File/DataWriter.h"

#include <boost/property_tree/ptree.hpp>

namespace Sorter {
    
    Settings& 
    Settings::operator<<(const boost::property_tree::ptree& rhs) {
        bins_path = rhs.get<std::string>("bins_path");
        patterns_path = rhs.get<std::string>("patterns_path");
        
        return *this;
    }
    
    std::ostream& operator<<(std::ostream& lhs, const Settings& rhs) {
        File::JsonDataWriter::write<Settings>(lhs, rhs);
        return lhs;
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Settings& rhs) {
        lhs.put("bins_path", rhs.bins_path);
        lhs.put("patterns_path", rhs.patterns_path); 
        
        return lhs;
    }
    
} /* namespace Sorter */


