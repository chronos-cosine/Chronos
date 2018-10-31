/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Bin.h"
#include "File/CsvDataWriter.h"
#include "File/JsonDataWriter.h"

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
    
    Bin&  
    Bin::operator<<(const boost::property_tree::ptree& rhs) {
        id = rhs.get<unsigned long long>("id");
        name = rhs.get<std::string>("name");
        parent_id = rhs.get<unsigned long long>("parent_id");
        
        return *this;
    }

    std::ostream& operator<<(std::ostream& lhs, const Bin& rhs) {
        File::JsonDataWriter::write<Bin>(lhs, rhs);
        return lhs;
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Bin& rhs) {
        lhs.put("id", rhs.id);
        lhs.put("name", rhs.name);
        lhs.put("parent_id", rhs.parent_id);
        
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