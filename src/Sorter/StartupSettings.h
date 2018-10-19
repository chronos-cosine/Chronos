/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StartupSettings.h
 * Author: user
 *
 * Created on 18 October 2018, 12:56 PM
 */

#ifndef SORTER_STARTUPSETTINGS_H
#define SORTER_STARTUPSETTINGS_H

#include "Notifier/INotifier.h"
#include "Sorter/PatternBinLinker.h"

#include <string>
#include <set>
#include <memory>

namespace Sorter {
    
    class StartupSettings {
    private:
        std::map<unsigned long long, std::shared_ptr<Pattern>> __patterns;
        std::map<unsigned long long, std::shared_ptr<Bin>> __bins;
        PatternBinLinker __pattern_bin_linker;
        std::shared_ptr<Notifier::INotifier> __notifier;
        
        std::string __log_file_directory;
        std::string __results_directory;
        std::string __completed_directory;
        std::set<std::string> __job_file_directories;
        
        std::string __sorter_trigger_extension;
        std::string __sorter_busy_extension;
        std::string __sorter_done_extension;
         
        std::string __notifier_type;
        std::string __patterns_file_location;
        std::string __patterns_file_type;
        std::string __bins_file_location;
        std::string __bins_file_type;
        
        unsigned short __sorter_count;
        unsigned short __log_file_reset_minutes;
    public:
        StartupSettings(const std::string& startup_settings_file);
        virtual ~StartupSettings();
    private:
        void set_notifier();
        void read_settings_file(const std::string& startup_settings_file);
        void read_patterns_file();
        void read_bins_file();
    public:
        std::map<unsigned long long, std::shared_ptr<Pattern>>& get_patterns();
        std::map<unsigned long long, std::shared_ptr<Bin>>& get_bins();
        std::shared_ptr<Notifier::INotifier>& get_notifier();
        
        const std::string& get_log_file_directory() const;
        const std::string& get_results_directory() const;
        const std::string& get_completed_directory() const;
        const std::set<std::string>& get_job_file_directories() const;
        
        const std::string& get_sorter_trigger_extension() const;
        const std::string& get_sorter_busy_extension() const;
        const std::string& get_sorter_done_extension() const;
         
        const std::string& get_notifier_type() const;
        const std::string& get_patterns_file_location() const;
        const std::string& get_patterns_file_type() const;
        const std::string& get_bins_file_location() const;
        const std::string& get_bins_file_type() const;
        
        const unsigned short& get_sorter_count() const;
        const unsigned short& get_log_file_reset_minutes() const;
    };
    
} /* namespace Sorter */

#endif /* SORTER_STARTUPSETTINGS_H */

