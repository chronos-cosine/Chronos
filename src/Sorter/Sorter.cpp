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
#include "Sorter/KeywordBooleanMatcher.h"
#include "KeywordBooleanMatcher.h"

#include <boost/filesystem/path.hpp>

namespace Sorter {
    
    Sorter::Sorter(PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& pattern_matching_machine,
                   Core::ConcurrentQueue<boost::filesystem::path>& concurrent_queue, 
                   const std::string& output_directory,
                   const std::string& output_directory, std::map<std::shared_ptr<Bin>, std::set<std::shared_ptr<Pattern>>>& bin_patterns) 
            : Core::IProcessor(30), __pattern_matching_machine(pattern_matching_machine),
              __concurrent_queue(concurrent_queue), __output_directory(output_directory),
              __bin_patterns(bin_patterns) {
        __pattern_matching_machine.completed().connect(__completed);
        __pattern_matching_machine.match_found().connect(__match_found);
    }

    Sorter::~Sorter() { }
    
    void 
    Sorter::process_job(const Job& job) {
        BinParentMatcher bin_parent_matcher;
        KeywordBooleanMatcher keyword_boolean_matcher;
        
        std::cout << "1 Sorter::process_job" << std::endl;
        keyword_boolean_matcher.match_boolean(__match_patterns[job], __match_bins[job], __bin_patterns);
        std::cout << "2 Sorter::process_job" << std::endl;
        bin_parent_matcher.match_parents(__match_bins[job]);
        std::cout << "3 Sorter::process_job" << std::endl;
        __result_file_writer.write(job, __match_patterns[job], __match_bins[job], __output_directory);
        std::cout << "4 Sorter::process_job" << std::endl;
    }
    
    bool 
    Sorter::process() {
        boost::filesystem::path job_path(__concurrent_queue.pop());
        std::unique_ptr<Job> job = __job_file_reader.read(job_path.string());
        if (nullptr == job) {
            return false;
        } else { 
            std::cout << "1 Sorter::process" << std::endl;
            __pattern_matching_machine.match(*job, *this);
            std::cout << "2 Sorter::process" << std::endl;
            return true;
        }
    }

}