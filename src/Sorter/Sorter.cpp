/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.cpp
 * Author: user
 * 
 * Created on 05 October 2018, 8:53 AM
 */

#define SORTER_SLEEP_TIME 5
#define SORTER_JOB_EXTENSION ".sjob"
#define SORTER_JOB_COMPLETED_EXTENSION ".sjobd"

#include "Core/INotifier.h"
#include "Core/IProcessor.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Result.h"

#include <boost/signals2.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>

namespace Sorter {
        
    Sorter::Sorter(const char* pattern_file, const char* bin_file, const char* job_path) 
                : Core::IProcessor(SORTER_SLEEP_TIME), __bins(__bin_file_reader.read(bin_file)),
                  __patterns(__pattern_file_reader.read(pattern_file)), __job_path(job_path),
                  __pattern_matching_machine(map_values_to_set(__patterns)) {
        initialise_sorter();
    }
    
    Sorter::Sorter(const char* pattern_file, const char* bin_file, const char* job_path, Core::INotifier* notifier)
                : Core::IProcessor(SORTER_SLEEP_TIME, notifier), __bins(__bin_file_reader.read(bin_file)),
                  __patterns(__pattern_file_reader.read(pattern_file)), __job_path(job_path),
                  __pattern_matching_machine(map_values_to_set(__patterns)) {
        initialise_sorter();
    }
        
    Sorter::~Sorter() { 
        __memory_management.free_bins(__bins);
        __memory_management.free_patterns(__patterns);
    }
    
    void 
    Sorter::initialise_sorter() {
        link_pattern_bin();
        __match_found_functor.__sorter = this;
        __pattern_matching_machine.match_found().connect(__match_found_functor);
    }

    void 
    Sorter::link_pattern_bin() {
        for (auto& p: __patterns) {
            Pattern* pattern = dynamic_cast<Pattern*>(p.second);
            if (__bins.find(pattern->get_bin_id()) != __bins.end()) {
                pattern->set_bin(__bins[pattern->get_bin_id()]);
            }
        }
    }
    
    bool 
    Sorter::process() {
        bool result = false;
        boost::filesystem::path job_path(__job_path);
        boost::filesystem::directory_iterator end_of_directory;
        
        for (boost::filesystem::directory_iterator iterator(job_path);
             iterator!= end_of_directory;
             ++iterator) {
            if (boost::filesystem::is_regular_file(*iterator)
                && boost::filesystem::extension(*iterator) == SORTER_JOB_EXTENSION) {
                if (!result) {
                    result = true;
                }
                
                std::string job_file_name((*iterator).path().string());
                Job* job(__job_file_reader.read(job_file_name.c_str()));
                PatternMatcher::IPattern input(job->get_document());
                __pattern_matching_machine.match(&input, this);
                Result result(job, &__matches[&input]);
                
                __result_file_writer.write(result, job_file_name.replace(job_file_name.find(SORTER_JOB_EXTENSION), 
                                                                         sizeof(SORTER_JOB_COMPLETED_EXTENSION) - 1,
                                                                         SORTER_JOB_COMPLETED_EXTENSION)
                                                                .c_str());
                
                boost::filesystem::remove(*iterator);
                
                __matches.erase(&input);
                delete job;
            }
        }
        
        return result;
    }
    
    
} /* namespace Sorter */
