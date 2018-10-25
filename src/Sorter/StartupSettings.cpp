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

#include "Exceptions/Exception.h"
#include "Notifier/CoutNotifier.h"
#include "Notifier/BlankNotifier.h"
#include "Notifier/INotifier.h"
#include "Notifier/LogFileNotifier.h"
#include "Sorter/Bin.h"
#include "Sorter/File/BinCsvFileReader.h"
#include "Sorter/Pattern.h"
#include "Sorter/PatternBinLinker.h"
#include "Sorter/File/PatternCsvFileReader.h"
#include "Sorter/StartupSettings.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <memory>

namespace Sorter {

    StartupSettings::~StartupSettings() { }
     
    StartupSettings::StartupSettings(const std::string& startup_settings_file) {
        read_settings_file(startup_settings_file);
        set_notifier();
        read_patterns_file();
        read_bins_file();
        PatternBinLinker().link(__patterns, __bins);
    }
    
    void 
    StartupSettings::read_patterns_file() {
        if (__patterns_file_type == "csv") {
            PatternCsvFileReader pattern_file_reader(__notifier);
            __patterns = pattern_file_reader.read(__patterns_file_location);
        } else {
            thrower ("Not yet implemented");
        }
    }
    
    void
    StartupSettings::read_bins_file() {
        if (__bins_file_type == "csv") {
            BinCsvFileReader bin_file_reader(__notifier);
            __bins = bin_file_reader.read(__bins_file_location);
        } else {
            thrower ("Not yet implemented");
        }
    }
    
    void 
    StartupSettings::read_settings_file(const std::string& startup_settings_file) {
       
    }
    
    std::map<unsigned long long, std::shared_ptr<Pattern>>& 
    StartupSettings::get_patterns() {
        return __patterns;
    }
    
    std::map<unsigned long long, std::shared_ptr<Bin>>& 
    StartupSettings::StartupSettings::get_bins() {
        return __bins;
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
    StartupSettings::get_log_file_directory() const {
        return __log_file_directory;
    }
    
    const std::string& 
    StartupSettings::get_results_directory() const {
        return __results_directory;
    }
    
    const std::string& 
    StartupSettings::get_completed_directory() const {
        return __completed_directory;
    }
    
    const std::set<std::string>& 
    StartupSettings::get_job_file_directories() const {
        return __job_file_directories;
    }

    const std::string& 
    StartupSettings::get_sorter_trigger_extension() const {
        return __sorter_trigger_extension;
    }
    
    const std::string& 
    StartupSettings::get_sorter_busy_extension() const {
        return __sorter_busy_extension;
    }
    
    const std::string& 
    StartupSettings::get_sorter_done_extension() const {
        return __sorter_done_extension;
    }

    const std::string& 
    StartupSettings::get_notifier_type() const {
        return __notifier_type;
    }
    
    const std::string& 
    StartupSettings::get_patterns_file_location() const {
        return __patterns_file_location;
    }
    
    const std::string& 
    StartupSettings::get_patterns_file_type() const {
        return __patterns_file_type;
    }
    
    const std::string& 
    StartupSettings::get_bins_file_location() const {
        return __bins_file_location;
    }
    
    const std::string& 
    StartupSettings::get_bins_file_type() const {
        return __bins_file_type;
    }

    const unsigned short& 
    StartupSettings::get_sorter_count() const {
        return __sorter_count;
    }
    
    const unsigned short& 
    StartupSettings::get_log_file_reset_minutes() const {
        return __log_file_reset_minutes;
    }
    
    std::shared_ptr<Notifier::INotifier>&
    StartupSettings::get_notifier() {
        return __notifier;
    }

    boost::property_tree::ptree& 
    operator<<(boost::property_tree::ptree& lhs, const StartupSettings& rhs) {
        lhs.put("log_file_directory", rhs.__log_file_directory);
        lhs.put("results_directory", rhs.__results_directory); 
        lhs.put("completed_directory", rhs.__completed_directory);
        lhs.put("sorter_trigger_extension", rhs.__sorter_trigger_extension); 
        lhs.put("sorter_busy_extension", rhs.__sorter_busy_extension);
        lhs.put("sorter_done_extension", rhs.__sorter_done_extension); 
        lhs.put("notifier_type", rhs.__notifier_type); 
        lhs.put("patterns_file_location", rhs.__patterns_file_location);
        lhs.put("patterns_file_type", rhs.__patterns_file_type); 
        lhs.put("bins_file_location", rhs.__bins_file_location);
        lhs.put("bins_file_type", rhs.__bins_file_type); 
        lhs.put("sorter_count", rhs.__sorter_count);
        lhs.put("log_file_reset_minutes", rhs.__log_file_reset_minutes);
        boost::property_tree::ptree directories;
        for (auto& directory: rhs.__job_file_directories) {
            boost::property_tree::ptree value;
            value.put("", directory);
            directories.push_back(std::make_pair("", value));
        }
        lhs.add_child("job_file_directories", directories);  
        
        return lhs;
    }
    
    std::ostream& 
    operator<<(std::ostream& lhs, const StartupSettings& rhs) {
        boost::property_tree::ptree ptree;
        ptree << rhs;

        boost::property_tree::write_json(lhs, ptree);
        return lhs;
    }

} /* namespace Sorter */