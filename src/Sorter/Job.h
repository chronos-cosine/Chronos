/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Job.h
 * Author: user
 *
 * Created on 31 October 2018, 7:07 AM
 */

#ifndef SORTER_JOB_H
#define SORTER_JOB_H

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>

namespace Sorter {
    struct Job {
        unsigned long long id;
        std::string document;
        
        bool operator<(const Job& rhs);
        bool operator==(const Job& rhs);
        bool operator!=(const Job& rhs);
        Bin& operator<<(const boost::property_tree::ptree& rhs);
        
        friend std::ostream& operator<<(std::ostream& lhs, const Job& rhs);
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Job& rhs);
        
    }; /* struct Job */
    
} /* namespace Sorter */
 

#endif /* SORTER_JOB_H */

