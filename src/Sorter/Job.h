/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Job.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 31 October 2018, 10:52 PM
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
        std::string filename;
        
        bool operator<(const Job& rhs) const;
        bool operator==(const Job& rhs) const;
        bool operator!=(const Job& rhs) const;
        Job& operator<<(const boost::property_tree::ptree& rhs);
        std::string::const_iterator begin() const;
        std::string::const_iterator end() const;
        
        friend std::ostream& operator<<(std::ostream& lhs, const Job& rhs);
        friend boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, const Job& rhs);
        
    }; /* struct Job */
    
} /* namespace Sorter */
 

#endif /* SORTER_JOB_H */

