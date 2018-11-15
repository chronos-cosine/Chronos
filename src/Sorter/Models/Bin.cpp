/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bin.cpp
 * Author: user
 * 
 * Created on 15 November 2018, 1:20 PM
 */

#include "Bin.h"

namespace Sorter {
    namespace Models {
        
        bool 
        Bin::operator==(const Bin& rhs) const noexcept {
            return id == rhs.id;
        }
        
        bool 
        Bin::operator!=(const Bin& rhs) const noexcept {
            return !(*this == rhs);
        }
        
        bool 
        Bin::operator<(const Bin& rhs) const noexcept {
            if (parent_id.is_initialized()) {
                if (rhs.parent_id.is_initialized()) {
                    if (parent_id.get() != rhs.parent_id.get()) {
                        return parent_id.get() < rhs.parent_id.get();
                    }
                } else {
                    return false;
                }
            } else if (rhs.parent_id.is_initialized()) {
                return true;
            }
            
            return id < rhs.id;
        }
        
    } /* namespace Models */
} /* namespace Sorter */

namespace std {
    
    template<>
    struct hash<Sorter::Models::Bin> {
        
        std::size_t 
        operator()(const Sorter::Models::Bin& bin) const {
            return std::hash<unsigned long long>{}(bin.id);
        }
        
    }; /* struct hash<Sorter::Models::Bin> */
    
} /* namespace std */