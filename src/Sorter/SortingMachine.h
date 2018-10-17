/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ConcurrentQueue.h"
#include "Processors/FileSpooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Bin.h"
#include "Sorter/PatternBinLinker.h"

#include <memory>
#include <vector>
#include <string>

namespace Sorter {

    class SortingMachine {
    private:
        PatternBinLinker __pattern_bin_linker;
        std::map<unsigned long long, std::shared_ptr<Pattern>> __patterns;
        std::map<unsigned long long, std::shared_ptr<Bin>> __bins; 
        Collections::ConcurrentQueue<boost::filesystem::path> __job_queue;
        PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter> __pattern_matching_machine;
        std::vector<std::shared_ptr<Processors::FileSpooler>> __file_spoolers;
        std::vector<std::shared_ptr<Sorter>> __sorters;
        std::string __to_sort_extension;
        std::string __busy_extension;
        std::shared_ptr<Notifier::INotifier> __notifier;
    public:
        SortingMachine(const std::string& pattern_file, const std::string& bin_file, 
                       const std::vector<std::string>& job_paths, unsigned int sorter_count,
                       const std::string& output_directory,
                       const std::string& to_sort_extension,
                       const std::string& busy_extension, 
                       std::shared_ptr<Notifier::INotifier> notifier);
        virtual ~SortingMachine();
        
        void start();
        void stop();
        void reset_folder_files(const std::string& folder);
    public:
        SortingMachine(const Sorter&) = delete;
        SortingMachine& operator=(const Sorter&) = delete;
        SortingMachine(const Sorter&&) = delete;
        SortingMachine& operator=(const Sorter&&) = delete;
    };  
    
} /* namespace Sorter */

#endif /* SORTER_SORTINGMACHINE_H */

