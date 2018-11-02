/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Result.cpp
 * Author: user
 * 
 * Created on 01 November 2018, 9:27 AM
 */

#include "Result.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Pattern.h"
 
#include <set>

namespace Sorter {
    
    std::ostream& operator<<(std::ostream& lhs, const Result& rhs) {
        boost::property_tree::ptree root;
        boost::property_tree::ptree job;
        job << *(rhs.job);
        root.push_back(std::make_pair("job", job));
        
        if (nullptr != rhs.bin_matches) {
            boost::property_tree::ptree bins;
            
            for (const auto& bin: *(rhs.bin_matches)) { 
                boost::property_tree::ptree value;
                boost::property_tree::ptree b;
                b << bin;
                value.push_back(std::make_pair("", b));
                bins.push_back(std::make_pair("", value));
            }
            root.push_back(std::make_pair("bin_matches", bins));
        }
        
        if (nullptr != rhs.pattern_matches) {
            boost::property_tree::ptree matches;
            
            for (const auto& pair: *(rhs.pattern_matches)) {
                matches.put("Position", pair.first);
                boost::property_tree::ptree patterns;
                
                for (const auto& pattern: pair.second) {
                    boost::property_tree::ptree value;
                    boost::property_tree::ptree p;
                    p << pattern;
                    value.push_back(std::make_pair("", p));
                    patterns.push_back(std::make_pair("", value));
                }
                matches.push_back(std::make_pair("patterns", patterns));
            }
            root.push_back(std::make_pair("pattern_matches", matches));
        }
        
        boost::property_tree::write_json(lhs, root);

        return lhs;
    }
       
} /* namespace Sorter */