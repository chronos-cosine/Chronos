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

#include "Collections/ConcurrentQueue.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/JobFileReader.h"
#include "Sorter/Pattern.h"
#include "Sorter/BinParentMatcher.h"
#include "Sorter/KeywordBooleanMatcher.h"

#include <boost/filesystem/path.hpp>
#include <boost/filesystem.hpp>

namespace Sorter {
    
    Sorter::Sorter(PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>& pattern_matching_machine,
                   Collections::ConcurrentQueue<boost::filesystem::path>& concurrent_queue, 
                   const std::string& output_directory, const std::shared_ptr<Notifier::INotifier>& notifier) 
            : __pattern_matching_machine(pattern_matching_machine),
              __concurrent_queue(concurrent_queue), __output_directory(output_directory),
              __notifier(notifier), Processors::IProcessor(5, notifier) {
        __pattern_matching_machine.completed().connect(__completed);
        __pattern_matching_machine.match_found().connect(__match_found);
    }

    Sorter::~Sorter() { }
    
    void 
    Sorter::process_job(const Job& job) {
        BinParentMatcher bin_parent_matcher;
        KeywordBooleanMatcher keyword_boolean_matcher;
        std::stringstream notification; 
        
        notification << "Performing boolean matches on " << job.get_filename();
        __notifier->notify(notification);
        
        keyword_boolean_matcher.match_boolean(__match_patterns[job], __match_bins[job]); 
        
        notification << "Checking tree parents " << job.get_filename();
        __notifier->notify(notification);
        
        bin_parent_matcher.match_parents(__match_bins[job]);
        
        notification << "Writing the results to file " << job.get_filename();
        __notifier->notify(notification);
        
        __result_file_writer.write(job, __match_patterns[job], __match_bins[job], __output_directory);
        
        boost::filesystem::path old_path(job.get_filename());
        std::stringstream new_path; 
        
        new_path << __output_directory << old_path.stem().string().c_str() << ".done";
        
        notification << "Marking job file as done " << job.get_filename(); 
        __notifier->notify(notification);
        
        boost::filesystem::rename(old_path, boost::filesystem::path(new_path.str()));
    }
    
    bool 
    Sorter::process() {  
        std::stringstream notification; 
        
        notification << "Popping off queue";
        __notifier->notify(notification);
        boost::filesystem::path job_path(__concurrent_queue.pop());
        
        notification << "Creating job for " << job_path;
        __notifier->notify(notification);
        std::unique_ptr<Job> job = __job_file_reader.read(job_path.string());
        
        if (nullptr != job) {
            notification << "Performing pattern matching " << job_path;
            __notifier->notify(notification);
            
            __pattern_matching_machine.match(*job, *this);
            return true;
        }
        
        return false;
    }
} /* namespace Sorter */