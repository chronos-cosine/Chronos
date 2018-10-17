/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/JobFileReader.h"

/* 
 * File:   JobFileReader.cpp
 * Author: user
 * 
 * Created on 10 October 2018, 9:15 AM
 */

#include "Exceptions/Exception.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Sorter {

    JobFileReader::JobFileReader() { }

    JobFileReader::~JobFileReader() { }
    
    std::unique_ptr<Job>
    JobFileReader::read(const std::string& filename) const
    { 
        std::ifstream file(filename.c_str());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            
            return std::unique_ptr<Job>(new Job(ptree.get<unsigned long long>("Id"),
                             ptree.get<std::string>("Document"),
                             filename));
        } else {
            thrower("Could not open job file.");
        }
        
        return std::unique_ptr<Job>(nullptr);
    }
        
} /* namespace Sorter */