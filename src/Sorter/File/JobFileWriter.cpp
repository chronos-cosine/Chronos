/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/File/JobFileWriter.h"

/* 
 * File:   JobFileWriter.cpp
 * Author: user
 * 
 * Created on 11 October 2018, 2:00 PM
 */


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <mutex>

namespace Sorter {

    JobFileWriter::JobFileWriter() { }
 
    JobFileWriter::~JobFileWriter() { }
    
    void 
    JobFileWriter::write(const Job& job) {
        std::lock_guard<std::mutex> lock(__mutex);
        
        std::ofstream output(job.get_filename());
        if (output.is_open()) {
            boost::property_tree::ptree root;
            root << job;
            
            boost::property_tree::write_json(output, root);
        }
    }

} /* namespace Sorter */