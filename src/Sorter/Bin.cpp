/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Bin.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

namespace Sorter {

    bool 
    Bin::operator<(const Bin& rhs) {
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
    
    boost::property_tree::ptree& operator<<(boost::property_tree::ptree& lhs, 
                                            const Bin& rhs) {
        lhs.put("Id", rhs.id);
        lhs.put("Name", rhs.name);
        lhs.put("ParentId", rhs.parent_id);
        
        return lhs;
    }
    
    Bin& operator<<(Bin& lhs, const boost::property_tree::ptree& rhs) {
        lhs.id = ptree.get<unsigned long long>("Id");
        lhs.name = ptree.get<std::string>("Name");
        lhs.parent_id = ptree.get<unsigned long long>("Id");
    }
    
    std::ostream& operator<<(std::ostream& lhs, const Bin& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs; 
        boost::property_tree::write_json(lhs, ptree);
        
        return lhs;
    }
        
} /* namespace Sorter */

namespace std {
    
    template <>
    struct hash<Sorter::Bin> {
        std::size_t 
        operator()(const Sorter::Bin bin) const {
            return std::hash<unsigned long long>{}(bin.id);
        }
    };
} /* namespace Sorter */