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

#include "Apps/Sorter/Models/Bin.h"

namespace Sorter {
    namespace Models {

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
        Bin::operator>>(boost::property_tree::ptree& lhs) const {
            lhs.put("id", id);
            lhs.put("name", name);

            if (is_root()) {
                lhs.put("parent_id", "null");
            } else {
                lhs.put("parent_id", parent_id.get());
            }

            return lhs;
        }
                
    } /* namespace Models */
} /* namespace Sorter */

namespace std {
    
    template<>
    struct hash<Sorter::Models::Bin> {
        
        std::size_t 
        operator()(const Sorter::Models::Bin& t_bin) const {
            return std::hash<unsigned long long>{}(t_bin.id);
        }
        
    }; /* struct hash<Sorter::Models::Bin> */
    
    template<>
    struct hash<std::shared_ptr<Sorter::Models::Bin>> {
        
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Models::Bin>& t_bin) const {
            if (nullptr == t_bin) {
                return 0;
            }
            
            return std::hash<unsigned long long>{}(t_bin->id);
        }
        
    }; /* struct hash<std::shared_ptr<Sorter::Models::Bin>> */
    
} /* namespace std */