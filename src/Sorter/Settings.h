/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.h
 * Author: user
 *
 * Created on 30 October 2018, 10:58 AM
 */

#ifndef SORTER_SETTINGS_H
#define SORTER_SETTINGS_H

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>

namespace Sorter {
    
    struct Settings {
        std::string patterns_path;
        std::string bins_path;
        
        Settings& operator<<(const boost::property_tree::ptree& rhs);
        
        friend std::ostream& operator<<(std::ostream& lhs, const Settings& rhs);
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Settings& rhs);
        
    }; /* struct Settings */
    
} /* namespace Sorter */

#endif /* SORTER_SETTINGS_H */

