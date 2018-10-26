/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Notifier/BlankNotifier.h"
#include "Notifier/CoutNotifier.h"
#include "Notifier/FileNotifier.h"
#include "Notifier/LogFileNotifier.h"
#include "Sorter/File/BinCsvFileReader.h"
#include "Sorter/File/PatternCsvFileReader.h"
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
    
    std::shared_ptr<Notifier::INotifier>
    StartupSettingsFileReader::get_notifier(const std::string& notifier_type,
            const std::string& log_directory,
            unsigned short log_file_reset_minutes) {
        if (notifier_type == "console") {
            return std::shared_ptr<Notifier::INotifier>(new Notifier::CoutNotifier());
         } else if (notifier_type == "blank") {
            return std::shared_ptr<Notifier::INotifier>(new Notifier::BlankNotifier());
         } else if (notifier_type == "log") {
            return std::shared_ptr<Notifier::INotifier>(new Notifier::LogFileNotifier(log_file_reset_minutes, 
                    log_directory));
         } else {
            thrower ("Not yet implemented");
         }
    }
    
    std::map<unsigned long long, std::shared_ptr<Pattern>>
    StartupSettingsFileReader::read_patterns_file(const std::string& patterns_file_type,
            const std::string& patterns_file_location,
            const std::shared_ptr<Notifier::INotifier>& notifier) {
        if (patterns_file_type == "csv") {
            PatternCsvFileReader pattern_file_reader(notifier);
            return pattern_file_reader.read(patterns_file_location);
        } else {
            thrower ("Not yet implemented");
        }
    }
    
    std::map<unsigned long long, std::shared_ptr<Bin>>
    StartupSettingsFileReader::read_bins_file(const std::string& bins_file_type,
            const std::string& bins_file_location,
            const std::shared_ptr<Notifier::INotifier>& notifier) {
        if (bins_file_type == "csv") {
            BinCsvFileReader bin_file_reader(notifier);
            return bin_file_reader.read(bins_file_location);
        } else {
            thrower ("Not yet implemented");
        }
    }

    StartupSettings
    StartupSettingsFileReader::read(const std::string& filename) {
        std::ifstream file(filename.c_str());
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();

            boost::property_tree::ptree ptree;
            boost::property_tree::read_json(buffer, ptree);
            
            std::string log_file_directory = ptree.get<std::string>("log_file_directory");
            std::string results_directory = ptree.get<std::string>("results_directory");
            std::string completed_directory = ptree.get<std::string>("completed_directory");
            
            std::string sorter_trigger_extension = ptree.get<std::string>("sorter_trigger_extension");
            std::string sorter_busy_extension = ptree.get<std::string>("sorter_busy_extension");
            std::string sorter_done_extension = ptree.get<std::string>("sorter_done_extension");
            
            std::string notifier_type = ptree.get<std::string>("notifier_type"); 
            std::string patterns_file_location = ptree.get<std::string>("patterns_file_location");
            std::string patterns_file_type = ptree.get<std::string>("patterns_file_type");
            std::string bins_file_location = ptree.get<std::string>("bins_file_location");
            std::string bins_file_type = ptree.get<std::string>("bins_file_type");
            
            unsigned short sorter_count = ptree.get<unsigned short>("sorter_count");
            unsigned short log_file_reset_minutes = ptree.get<unsigned short>("log_file_reset_minutes");
            
            std::shared_ptr<Notifier::INotifier> notifier = get_notifier(notifier_type, log_file_directory, log_file_reset_minutes);
            std::set<std::string> job_file_directories;
            for (auto& item: ptree.get_child("job_file_directories")) {
                job_file_directories.insert(item.second.get_value<std::string>());
            }
            
            auto patterns = read_patterns_file(patterns_file_type, patterns_file_location, notifier);
            auto bins = read_bins_file(bins_file_type, bins_file_location, notifier);
            PatternBinLinker().link(patterns, bins);
            
            return StartupSettings(patterns,
                                   bins,
                                   notifier,
                                   log_file_directory,
                                   results_directory,
                                   completed_directory,
                                   job_file_directories,
                                   sorter_trigger_extension,
                                   sorter_busy_extension,
                                   sorter_done_extension,
                                   notifier_type,
                                   patterns_file_location,
                                   patterns_file_type,
                                   bins_file_location,
                                   bins_file_type,
                                   sorter_count,
                                   log_file_reset_minutes); 
        } else {
            thrower("Could not open startup settings file.");
        }
    }

} /* namespace Sorter */