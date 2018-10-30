/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bin.h
 * Author: user
 *
 * Created on 29 October 2018, 8:34 AM
 */

#ifndef SORTER_BIN_H
#define SORTER_BIN_H

#include <iostream>
#include <string>
#include <vector>

namespace Sorter {
    
    struct Bin {
        unsigned long long id;
        std::string name;
        unsigned long long parent_id;

        bool operator<(const Bin& rhs);
        bool operator==(const Bin& rhs);
        bool operator!=(const Bin& rhs);
        Bin& operator<<(const std::vector<std::string>& rhs);
        
        friend std::ostream& operator<<(std::ostream& lhs, const Bin& rhs);
    };  /* struct Bin */
    
} /* namespace Sorter */


#endif /* SORTER_BIN_H */

