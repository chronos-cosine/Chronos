/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StartupSettings.cpp
 * Author: user
 * 
 * Created on 18 October 2018, 12:56 PM
 */

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Sorter/StartupSettings.h"
#include "Exceptions/Exception.h"
#include "Notifier/CoutNotifier.h"
#include "Notifier/BlankNotifier.h"
#include "Notifier/INotifier.h"
#include "Notifier/LogFileNotifier.h"
#include <iostream>
#include <fstream>
#include <memory>

namespace Sorter {

    StartupSettings::~StartupSettings() { }
    
    StartupSettings::StartupSettings(const std::string& startup_settings_file) {
        std::ifstream file(startup_settings_file.c_str());
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
            
            set_notifier();
            
        } else {
            thrower("Could not open startup settings file.");
        }
    }
    
    void
    StartupSettings::set_notifier() {
        if (__notifier_type == "console") {
            __notifier = std::shared_ptr<Notifier::INotifier>(new Notifier::CoutNotifier());
        } else if (__notifier_type == "blank") {
            __notifier = std::shared_ptr<Notifier::INotifier>(new Notifier::BlankNotifier());
        } else if (__notifier_type == "log") {
            __notifier = std::shared_ptr<Notifier::INotifier>(new Notifier::LogFileNotifier(__log_file_reset_minutes, __log_file_directory));
        } else {
            __notifier = std::shared_ptr<Notifier::INotifier>(new Notifier::CoutNotifier());
        }
    }
    
    const std::string& 
    StartupSettings::get_log_file_directory(){
        return __log_file_directory;
    }
    
    const std::string& 
    StartupSettings::get_results_directory(){
        return __results_directory;
    }
    
    const std::string& 
    StartupSettings::get_completed_directory(){
        return __completed_directory;
    }
    
    const std::set<std::string>& 
    StartupSettings::get_job_file_directories(){
        return __job_file_directories;
    }

    const std::string& 
    StartupSettings::get_sorter_trigger_extension(){
        return __sorter_trigger_extension;
    }
    
    const std::string& 
    StartupSettings::get_sorter_busy_extension(){
        return __sorter_busy_extension;
    }
    
    const std::string& 
    StartupSettings::get_sorter_done_extension(){
        return __sorter_done_extension;
    }

    const std::string& 
    StartupSettings::get_notifier_type(){
        return __notifier_type;
    }
    
    const std::string& 
    StartupSettings::get_patterns_file_location(){
        return __patterns_file_location;
    }
    
    const std::string& 
    StartupSettings::get_patterns_file_type(){
        return __patterns_file_type;
    }
    
    const std::string& 
    StartupSettings::get_bins_file_location(){
        return __bins_file_location;
    }
    
    const std::string& 
    StartupSettings::get_bins_file_type(){
        return __bins_file_type;
    }

    const unsigned short& 
    StartupSettings::get_sorter_count(){
        return __sorter_count;
    }
    
    const unsigned short& 
    StartupSettings::get_log_file_reset_minutes(){
        return __log_file_reset_minutes;
    }
    
    const std::shared_ptr<Notifier::INotifier>&
    StartupSettings::get_notifier() {
        return __notifier;
    }


} /* namespace Sorter */