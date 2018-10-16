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
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/Pattern.h"
#include "Sorter/BinParentMatcher.h"

#include <boost/filesystem/path.hpp>

namespace Sorter {
    
    Sorter::Sorter(PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& pattern_matching_machine,
               Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue) 
            : Core::IProcessor(30), __pattern_matching_machine(pattern_matching_machine),
                    __concurrent_queue(concurrent_queue) {
        __pattern_matching_machine.completed().connect(__completed);
        __pattern_matching_machine.match_found().connect(__match_found);
    }

    Sorter::~Sorter() { }
    
    void 
    Sorter::process_job(const Job& job) {
        BinParentMatcher bin_parent_matcher;
        
        bin_parent_matcher.parents_exist(__match_bins[job]);
    }
    
    bool 
    Sorter::process() {
        boost::filesystem::path job_path(__concurrent_queue.pop());
        std::unique_ptr<Job> job = __job_file_reader.read(job_path.string());
        if (nullptr == job) {
            return false;
        } else { 
            __pattern_matching_machine.match(*job, *this);
            return true;
        }
    }

}