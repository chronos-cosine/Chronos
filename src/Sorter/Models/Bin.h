/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bin.h
 * Author: user
 *
 * Created on 15 November 2018, 1:20 PM
 */

#ifndef SORTER_MODELS_BIN_H
#define SORTER_MODELS_BIN_H

#include "Sorter/Models/BooleanOperator.h"

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>
#include <memory>
#include <map>
#include <set>
#include <string>

namespace Sorter {
    namespace Models {
        
        struct Pattern;
        
        struct Bin {
            unsigned long long id;
            std::string name;
            boost::optional<unsigned long long> parent_id;
            
            boost::optional<std::shared_ptr<Bin>> parent;
            std::map<Sorter::Models::BooleanOperator, 
                     std::set<std::shared_ptr<Pattern>>> patterns;
            bool is_root() const noexcept;
            
            bool operator==(const Bin& rhs) const noexcept;
            bool operator!=(const Bin& rhs) const noexcept;
            bool operator<(const Bin& rhs) const noexcept;
            Bin& operator=(const Bin& rhs);
            Bin& operator<<(const std::vector<std::string>& rhs);
            
            friend boost::property_tree::ptree& 
            operator<<(boost::property_tree::ptree& lhs, const Bin& bin);
            
        }; /* struct Bin */
        
    } /* namespace Models */
} /* namespace Sorter */

#endif /* SORTER_MODELS_BIN_H */

