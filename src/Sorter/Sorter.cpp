/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Sorter/Sorter.h"

/* 
 * File:   Sorter.cpp
 * Author: user
 * 
 * Created on 12 October 2018, 1:50 PM
 */

#include "Core/ConcurrentQueue.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/Pattern.h"

#include <boost/filesystem/path.hpp>

namespace Sorter {
    
    Sorter::Sorter(PatternMatcher::PatternMatchingMachine<std::string, Pattern, Sorter>& pattern_matching_machine,
               Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue) 
        : Core::IProcessor(30), __pattern_matching_machine(pattern_matching_machine),
               __concurrent_queue(concurrent_queue) { 
        
    }

    Sorter::~Sorter() { }
    
    bool 
    Sorter::process() {
        boost::filesystem::path job_path(__concurrent_queue.pop());
        std::unique_ptr<Job> job = __job_file_reader.read(job_path.string().c_str());
        if (nullptr == job) {
            return false;
        } else {
            return true;
        }
    }

}