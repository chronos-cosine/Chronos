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

namespace Sorter {
    
    SortingMachine::SortingMachine(const std::string& pattern_file, const std::string& bin_file, 
                       const std::vector<std::string>& job_paths, unsigned int sorter_count,
                       const std::string& output_directory,
                       const std::string& to_sort_extension,
                       const std::string& busy_extension, 
                       std::shared_ptr<Notifier::INotifier> notifier) 
                : __patterns(PatternCsvFileReader(notifier).read(pattern_file)), 
                  __bins(BinCsvFileReader(notifier).read(bin_file)), __to_sort_extension(to_sort_extension),
                  __busy_extension(busy_extension), __notifier(notifier),
                  __pattern_matching_machine(Core::Helpers::get_value_set<unsigned long long, std::shared_ptr<Pattern>>(__patterns)) {
        
        __pattern_bin_linker.link(__patterns, __bins);
        for (auto& job_path: job_paths) {
            reset_folder_files(job_path);
            __file_spoolers.push_back(std::shared_ptr<Processors::FileSpooler>(
                new Processors::FileSpooler(
                    job_path.c_str(), 
                    __to_sort_extension.c_str(), 
                    busy_extension.c_str(), 
                    __job_queue,
                    __notifier
                )));
        }
        
        for (int i = 0; i < sorter_count; ++i) {
            __sorters.push_back(std::shared_ptr<Sorter>(
                new Sorter(__pattern_matching_machine, 
                    __job_queue, 
                    output_directory,
                    __notifier)));
        }
    }
    
    SortingMachine::~SortingMachine() { 
        stop();
        __file_spoolers.clear();
        __sorters.clear();
    }
    
    void 
    SortingMachine::reset_folder_files(const std::string& folder) {
        boost::filesystem::path directory(folder);
        boost::filesystem::directory_iterator end_of_directory;
         
        for (boost::filesystem::directory_iterator iterator(directory);
             iterator!= end_of_directory;
             ++iterator) { 
            if (boost::filesystem::is_regular_file(*iterator)
                && boost::filesystem::extension(*iterator) == __busy_extension) {
                std::stringstream new_path; 
                new_path << folder << (*iterator).path().stem().c_str() << __to_sort_extension;  
                boost::filesystem::rename(*iterator, boost::filesystem::path(new_path.str()));
            }
        }
    }
    
    void 
    SortingMachine::start() { 
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
                __notifier->notify("waiting for spooler to exit...");
                std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
            }
        }
        for (auto& sorter: __sorters) {
            sorter->stop();
            
            while (sorter->get_is_running()) {
                __notifier->notify("waiting for sorter to exit...");
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }
    
} /* namespace Sorter */
