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

#define SORTER_ID_KEY "Id"
#define SORTER_DOCUMENT_KEY "Document"

#include "JobFileReader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace Sorter {

    JobFileReader::JobFileReader() { }

    JobFileReader::~JobFileReader() { }
    
    Job* 
    JobFileReader::read(const char* job_file_name)
    { 
        Job* object = nullptr;
        std::ifstream file(job_file_name);
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            
            object = new Job(ptree.get<unsigned long long>(SORTER_ID_KEY),
                             ptree.get<std::string>(SORTER_DOCUMENT_KEY).c_str());

            file.close(); 
        }
        
        return object;
    }
        
} /* namespace Sorter */