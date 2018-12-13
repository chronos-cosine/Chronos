/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 * 
 * Created on 16 November 2018, 8:01 PM
 */

#include "Apps/Sorter/Models/Pattern.h"

namespace Sorter {
    namespace Models {
          
        std::string::const_iterator 
        Pattern::begin() const {
            return value.begin();
        }
        
        std::string::const_iterator 
        Pattern::end() const {
            return value.end();
        }
        
        bool 
        Pattern::operator==(const Pattern& rhs) const noexcept {
            return id == rhs.id;
        }
        
        bool  
        Pattern::operator!=(const Pattern& rhs) const noexcept {
            return !(*this == rhs);
        }
        
        bool  
        Pattern::operator<(const Pattern& rhs) const noexcept {
            if (bin_id == rhs.bin_id) {
                if (boolean_operator == rhs.boolean_operator) {
                    return id < rhs.id;
                } else {
                    return boolean_operator < rhs.boolean_operator;
                }
            } else {
                return bin_id == rhs.bin_id;
            }
        }
        
        Pattern&  
        Pattern::operator=(const Pattern& rhs) {
            id = rhs.id;
            value = rhs.value;
            boolean_operator = rhs.boolean_operator;
            bin_id = rhs.bin_id;
            
            return *this;
        }
        
        Pattern&  
        Pattern::operator<<(const std::vector<std::string>& rhs) {
            id = std::stoull(rhs[0]);
            value = rhs[1];
            bin_id = std::stoull(rhs[2]);
            boolean_operator = (BooleanOperator)std::stoi(rhs[3]);
            
            return *this;
        }
        
        boost::property_tree::ptree& 
        Pattern::operator>>(boost::property_tree::ptree& lhs) const {
            lhs.put("id", id);
            lhs.put("value", value);
            lhs.put("boolean_operator", boolean_operator);
            lhs.put("bin_id", bin_id);
            
            return lhs;
        }
            
    } /* namespace Models */
} /* namespace Sorter */

namespace std {
    
    template<>
    struct hash<Sorter::Models::Pattern> {
        
        std::size_t 
        operator()(const Sorter::Models::Pattern& t_pattern) const {
            return std::hash<unsigned long long>{}(t_pattern.id);
        }
        
    }; /* struct hash<Sorter::Models::Pattern> */
    
    
    template<>
    struct hash<std::shared_ptr<Sorter::Models::Pattern>> {
        
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Models::Pattern>& t_pattern) const {
            if (nullptr == t_pattern) {
                return 0;
            }
            
            return std::hash<unsigned long long>{}(t_pattern->id);
        }
        
    }; /* struct hash<std::shared_ptr<Sorter::Models::Pattern>> */
    
} /* namespace std */
