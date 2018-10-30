/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Bin.h"

#include <exception>
#include <iostream>

namespace Sorter {

    bool 
    Bin::operator<(const Bin& rhs) {
        if (parent_id < rhs.parent_id) {
            return true;
        }
            
        return id < rhs.id;
    }

    bool 
    Bin::operator==(const Bin& rhs) {
        return id == rhs.id;
    }

    bool 
    Bin::operator!=(const Bin& rhs) {
        return !(*this == rhs);
    }
    
    Bin& 
    Bin::operator<<(const std::vector<std::string>& rhs) {
        if (rhs.size() != 3) { 
            throw std::runtime_error("Bin operator<< requires size() == 3");
        }
        
        id = std::stoull(rhs[0]);
        name = rhs[1];
        
        if (rhs[2].size() > 0) {
            parent_id = std::stoull(rhs[2]);
        } else {
            parent_id = 0;
        }
        
        return *this;
    }

    std::ostream& operator<<(std::ostream& lhs, const Bin& rhs) {
        lhs << "{\"Id\": \"" << rhs.id
            << "\", \"Name\": \"" << rhs.name
            << "\", \"Parent_Id\": \"" << rhs.parent_id
            << "\"}";
        
        return lhs;
    }
        
} /* namespace Sorter */

namespace std {
    
    template <>
    struct hash<Sorter::Bin> {
        std::size_t 
        operator()(const Sorter::Bin& bin) const {
            return std::hash<unsigned long long>{}(bin.id);
        }
    };
} /* namespace std */