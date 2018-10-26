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
     
    StartupSettings::StartupSettings(const std::map<unsigned long long, std::shared_ptr<Pattern>>& patterns,
                                     const std::map<unsigned long long, std::shared_ptr<Bin>>& bins,
                                     const std::shared_ptr<Notifier::INotifier>& notifier,
                                     const std::string& log_file_directory,
                                     const std::string& results_directory,
                                     const std::string& completed_directory,
                                     const std::set<std::string>& job_file_directories,
                                     const std::string& sorter_trigger_extension,
                                     const std::string& sorter_busy_extension,
                                     const std::string& sorter_done_extension,
                                     const std::string& notifier_type,
                                     const std::string& patterns_file_location,
                                     const std::string& patterns_file_type,
                                     const std::string& bins_file_location,
                                     const std::string& bins_file_type,
                                     const unsigned short& sorter_count,
                                     const unsigned short& log_file_reset_minutes)
        : __patterns(patterns), __bins(bins), 
          __notifier(notifier), __log_file_directory(log_file_directory), 
          __results_directory(results_directory), __completed_directory(completed_directory),
          __job_file_directories(job_file_directories), __sorter_trigger_extension(sorter_trigger_extension),
          __sorter_busy_extension(sorter_busy_extension), __sorter_done_extension(sorter_done_extension),
          __notifier_type(notifier_type), __patterns_file_location(patterns_file_location), 
          __patterns_file_type(patterns_file_type), __bins_file_location(bins_file_location), 
          __bins_file_type(bins_file_type), __sorter_count(sorter_count), 
          __log_file_reset_minutes(log_file_reset_minutes) { }
        
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
    
    std::map<unsigned long long, std::shared_ptr<Pattern>>& 
    StartupSettings::get_patterns() {
        return __patterns;
    }
    
    std::map<unsigned long long, std::shared_ptr<Bin>>& 
    StartupSettings::get_bins() {
        return __bins;
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