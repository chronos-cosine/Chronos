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

#include <boost/optional.hpp>
#include <string>
#include <vector>

#include "Bin.h"

namespace Sorter {
    namespace Models {
        
        bool
        operator==(const std::shared_ptr<Bin>& lhs, 
                   const std::shared_ptr<Bin>& rhs) {
            if (lhs == nullptr
                && rhs == nullptr) {
                return true;
            } else if (lhs == nullptr
                || rhs == nullptr) {
                return false;
            }
            
            return (*lhs == *rhs);
        }
        
        bool
        operator!=(const std::shared_ptr<Bin>& lhs, 
                   const std::shared_ptr<Bin>& rhs) {
            return !(lhs == rhs);
        }
        
        bool
        operator<(const std::shared_ptr<Bin>& lhs, 
                  const std::shared_ptr<Bin>& rhs) {
            if (lhs == nullptr
                && rhs == nullptr) {
                return false;
            } else if (lhs == nullptr) {
                return true;
            } else if (rhs == nullptr) {
                return false;
            }
            
            return (*lhs < *rhs);
        }
        
        bool
        Bin::is_root() const noexcept {
            return !parent_id.is_initialized();
        }
        
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
        
        Bin& 
        Bin::operator=(const Bin& rhs) {
            id = rhs.id;
            name = rhs.name;
            if (rhs.is_root()) {
                parent_id = boost::optional<unsigned long long>();
            } else {
                parent_id = boost::optional<unsigned long long>(rhs.parent_id.get());
            }
            
            return *this;
        }
        
        Bin& 
        Bin::operator<<(const std::vector<std::string>& rhs) {
            id = std::stoull(rhs[0]);
            name = rhs[1];
            unsigned long long temp = std::stoull(rhs[2]);
            if (temp > 0) {
                parent_id = boost::optional<unsigned long long>(temp);
            } else {
                parent_id = boost::optional<unsigned long long>();
            }
            
            return *this;
        }
        
        boost::property_tree::ptree& 
        operator<<(boost::property_tree::ptree& lhs, const Bin& bin) {
            lhs.put("id", bin.id);
            
            return lhs;
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