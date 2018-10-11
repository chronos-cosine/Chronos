/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   JobFileReader.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 9:15 AM
 */


#include "Sorter/JobFileReader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Sorter {

    JobFileReader::JobFileReader() { }

    JobFileReader::~JobFileReader() { }
    
    Job*
    JobFileReader::read(const char* filename) const
    { 
        Job* object = nullptr;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            
            object = new Job(ptree.get<unsigned long long>("Id"),
                             ptree.get<std::string>("Document").c_str(),
                             filename);
        } else {
            throw std::runtime_error("Could not open job file.");
        }
        
        return object;
    }
        
} /* namespace Sorter */