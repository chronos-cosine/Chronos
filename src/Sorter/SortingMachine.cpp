/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/SortingMachine.h"

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 05 October 2018, 8:53 AM
 */
 
#include "Core/Helpers.h" 
#include "Sorter/PatternCsvFileReader.h"
#include "Sorter/BinCsvFileReader.h"
#include "Notifier/INotifier.h"

#include <boost/filesystem.hpp>
#include <thread>
#include <set>
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>

namespace Sorter {
    
    SortingMachine::SortingMachine(StartupSettings& startup_settings) 
            : __startup_settings(startup_settings), 
              __pattern_matching_machine(
                Core::Helpers::get_value_set<unsigned long long, std::shared_ptr<Pattern>>(
                    startup_settings.get_patterns())) {
        
        for (const auto& job_path: __startup_settings.get_job_file_directories()) {
            reset_folder_files(job_path);
            __file_spoolers.push_back(std::shared_ptr<Processors::FileSpooler>(
                new Processors::FileSpooler(
                    job_path, 
                    __startup_settings.get_sorter_trigger_extension(),
                    __startup_settings.get_sorter_busy_extension(),
                    __job_queue,
                    __startup_settings.get_notifier(),
                    30
                )));
        }
        
        for (int i = 0; i < __startup_settings.get_sorter_count(); ++i) {
            __sorters.push_back(std::shared_ptr<Sorter>(
                new Sorter(
                    __pattern_matching_machine, 
                    __job_queue, 
                    30,
                    __startup_settings
                )));
        }
    }
    
    SortingMachine::~SortingMachine() { 
        stop();
        __file_spoolers.clear();
        __sorters.clear();
    }
    
    void 
    SortingMachine::reset_folder_files(const std::string& folder) {
        std::stringstream notification;
        notification << "Resetting " << folder;
        __startup_settings.get_notifier()->notify(notification);
        
        boost::filesystem::path directory(folder);
        boost::filesystem::directory_iterator end_of_directory;
         
        for (boost::filesystem::directory_iterator iterator(directory);
             iterator!= end_of_directory;
             ++iterator) { 
            if (boost::filesystem::is_regular_file(*iterator)
                && boost::filesystem::extension(*iterator) == __startup_settings.get_sorter_busy_extension()) {
                std::stringstream new_path; 
                new_path << folder << (*iterator).path().stem().c_str() << __startup_settings.get_sorter_trigger_extension();  
                boost::filesystem::rename(*iterator, boost::filesystem::path(new_path.str()));
            }
        }
    }
    
    void 
    SortingMachine::start() { 
        std::stringstream notification;
        
        for (auto& file_spooler: __file_spoolers) {
            std::thread thread(&Processors::FileSpooler::start, file_spooler);
            thread.detach();
        }
        
        for (auto& sorter: __sorters) {
            std::thread thread(&Sorter::start, sorter);
            thread.detach();
        } 
    }
    
    void 
    SortingMachine::stop() {
        for (auto& spooler: __file_spoolers) {
            spooler->stop();
            
            while (spooler->get_is_running()) {
                __startup_settings.get_notifier()->notify("waiting for spooler to exit...");
                std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
            }
        }
        for (auto& sorter: __sorters) {
            sorter->stop();
            
            while (sorter->get_is_running()) {
                __startup_settings.get_notifier()->notify("waiting for sorter to exit...");
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }
    
} /* namespace Sorter */
