/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Bin.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 29 October 2018, 10:52 PM
 */

#ifndef SORTER_BIN_H
#define SORTER_BIN_H

#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace Sorter {
    
    struct Bin {
        unsigned long long id;
        unsigned long long parent_id;
        std::string name;

        bool operator<(const Bin& rhs) const;
        bool operator==(const Bin& rhs) const;
        bool operator!=(const Bin& rhs) const;
        Bin& operator<<(const std::vector<std::string>& rhs);
        Bin& operator<<(const boost::property_tree::ptree& rhs);
        
        friend std::ostream& operator<<(std::ostream& lhs, const Bin& rhs);
        friend boost::property_tree::ptree& 
            operator<<(boost::property_tree::ptree& lhs, const Bin& rhs);
        
    };  /* struct Bin */
    
} /* namespace Sorter */


#endif /* SORTER_BIN_H */

