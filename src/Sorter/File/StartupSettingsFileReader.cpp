/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/File/StartupSettingsFileReader.h"

/* 
 * File:   StartupSettingsFileReader.cpp
 * Author: user
 * 
 * Created on 19 October 2018, 9:33 PM
 */

#include "Exceptions/Exception.h"

namespace Sorter {

    StartupSettingsFileReader::~StartupSettingsFileReader() { }

    StartupSettingsFileReader::StartupSettingsFileReader() { }

    StartupSettings
    StartupSettingsFileReader::read(const std::string& filename) const {
        std::ifstream file(filename.c_str());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            
            __log_file_directory = ptree.get<std::string>("log_file_directory");
            __results_directory = ptree.get<std::string>("results_directory");
            __completed_directory = ptree.get<std::string>("completed_directory");
            
            __sorter_trigger_extension = ptree.get<std::string>("sorter_trigger_extension");
            __sorter_busy_extension = ptree.get<std::string>("sorter_busy_extension");
            __sorter_done_extension = ptree.get<std::string>("sorter_done_extension");
            
            __notifier_type = ptree.get<std::string>("notifier_type"); 
            __patterns_file_location = ptree.get<std::string>("patterns_file_location");
            __patterns_file_type = ptree.get<std::string>("patterns_file_type");
            __bins_file_location = ptree.get<std::string>("bins_file_location");
            __bins_file_type = ptree.get<std::string>("bins_file_type");
            
            __sorter_count = ptree.get<unsigned short>("sorter_count");
            __log_file_reset_minutes = ptree.get<unsigned short>("log_file_reset_minutes");
             
            for (auto& item: ptree.get_child("job_file_directories")) {
                __job_file_directories.insert(item.second.get_value<std::string>());
            }
            
            return StartupSettings(__patterns,
                                   __bins,
                                   __pattern_bin_linker,
                                   __notifier,
                                   __log_file_directory,
                                   __results_directory,
                                   __completed_directory,
                                   __job_file_directories,
                                   __sorter_trigger_extension,
                                   __sorter_busy_extension,
                                   __sorter_done_extension,
                                   __notifier_type,
                                   __patterns_file_location,
                                   __patterns_file_type,
                                   __bins_file_location,
                                   __bins_file_type,
                                   __sorter_count,
                                   __log_file_reset_minutes);
        } else {
            thrower("Could not open startup settings file.");
        }
    }

};

} /* namespace Sorter */