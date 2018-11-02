/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Settings.cpp
 * Author: user
 * 
 * Created on 30 October 2018, 10:58 AM
 */

#include "Settings.h"
#include "File/JsonDataWriter.h"

#include <boost/property_tree/ptree.hpp>

namespace Sorter {
    
    Settings& 
    Settings::operator<<(const boost::property_tree::ptree& rhs) {
        log_file_directory = rhs.get<std::string>("log_file_directory");
        result_output_directory = rhs.get<std::string>("result_output_directory");
        completed_directory = rhs.get<std::string>("completed_directory");
        trigger_extension = rhs.get<std::string>("trigger_extension");
        busy_extension = rhs.get<std::string>("busy_extension");
        completed_extension = rhs.get<std::string>("completed_extension");
        patterns_path = rhs.get<std::string>("patterns_path");
        patterns_file_type = rhs.get<std::string>("patterns_file_type");
        bins_path = rhs.get<std::string>("bins_path");
        bins_file_type = rhs.get<std::string>("bins_file_type");
        instances = rhs.get<unsigned short>("instances");
        log_file_reset_minutes = rhs.get<unsigned short>("log_file_reset_minutes");
        completed_directory = rhs.get<std::string>("completed_directory");
        result_output_directory = rhs.get<std::string>("result_output_directory");
         
        for (auto& item: rhs.get_child("job_file_directories")) {
            job_file_directories.push_back(item.second.get_value<std::string>());
        }
        
        return *this;
    }
    
    std::ostream& operator<<(std::ostream& lhs, const Settings& rhs) {
        File::JsonDataWriter<Settings>::write(lhs, rhs);
        return lhs;
    }
    
    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const Settings& rhs) {
        lhs.put("log_file_directory", rhs.log_file_directory); 
        lhs.put("result_output_directory", rhs.result_output_directory); 
        lhs.put("completed_directory", rhs.completed_directory); 
        lhs.put("trigger_extension", rhs.trigger_extension); 
        lhs.put("busy_extension", rhs.busy_extension); 
        lhs.put("completed_extension", rhs.completed_extension); 
        lhs.put("patterns_path", rhs.patterns_path); 
        lhs.put("patterns_file_type", rhs.patterns_file_type); 
        lhs.put("bins_path", rhs.bins_path); 
        lhs.put("bins_file_type", rhs.bins_file_type); 
        lhs.put("instances", rhs.instances); 
        lhs.put("log_file_reset_minutes", rhs.log_file_reset_minutes); 
        lhs.put("completed_directory", rhs.completed_directory);
        
        boost::property_tree::ptree job_file_directories;
        for (const auto& job_file_directory: rhs.job_file_directories) {
            boost::property_tree::ptree value;
            value.put("", job_file_directory);
            job_file_directories.push_back(std::make_pair("", value));
        }
        lhs.add_child("job_file_directories", job_file_directories);
        
        return lhs;
    }
    
} /* namespace Sorter */


