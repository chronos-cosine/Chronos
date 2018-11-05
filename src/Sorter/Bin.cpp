/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/Bin.cpp
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 09 October 2018, 10:52 PM
 */

#include "Bin.h"
#include "File/CsvDataWriter.h"
#include "File/JsonDataWriter.h"

#include <exception>
#include <iostream>

namespace Sorter {

    bool 
    Bin::operator<(const Bin& rhs) const {
        if (parent_id < rhs.parent_id) {
            return true;
        }
            
        return id < rhs.id;
    }
    
    bool 
    Bin::operator==(const Bin& rhs) const {
        return id == rhs.id;
    }
    

    bool 
    Bin::operator!=(const Bin& rhs) const {
        return !(*this == rhs);
    }
    
    Bin& 
    Bin::operator<<(const std::vector<std::string>& rhs) {
        if (rhs.size() != 3) { 
            throw std::runtime_error("Bin operator<< std::vector<std::string>& requires size() == 3");
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
    
    //friend operators
    bool
    operator<(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return false;
        } else if (nullptr == lhs) {
            return true;
        } else if (nullptr == rhs) {
            return false;
        }
        
        return *lhs < *rhs;
    }

    bool
    operator==(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs) {
        if (nullptr == lhs && nullptr == rhs) {
            return true;
        } else if (nullptr == lhs || nullptr == rhs) {
            return false;
        }
        
        return *lhs == *rhs;
    }
    
    bool
    operator!=(const std::shared_ptr<Bin>& lhs, const std::shared_ptr<Bin>& rhs) {
        return !(lhs == rhs);
    }

    std::ostream& 
    operator<<(std::ostream& lhs, const Bin& rhs) {
        File::JsonDataWriter<Bin>::write(lhs, rhs);
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
    
    template <>
    struct hash<std::shared_ptr<Sorter::Bin>> {
        std::size_t 
        operator()(const std::shared_ptr<Sorter::Bin>& bin) const {
            if (nullptr == bin) {
                return 0;
            }
            return std::hash<unsigned long long>{}(bin->id);
        }
    };
    
} /* namespace std */