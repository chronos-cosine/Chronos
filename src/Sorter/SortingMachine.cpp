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
#include <thread>
#include <set>
#include <map>
#include <string>

namespace Sorter {
    
    SortingMachine::SortingMachine(const std::string& pattern_file, const std::string& bin_file, 
            const std::vector<std::string>& job_paths, unsigned int sorter_count) 
        : __patterns(PatternCsvFileReader().read(pattern_file)), __bins(BinCsvFileReader().read(bin_file)),
          __pattern_matching_machine(Core::Helpers::get_value_set<unsigned long long, std::shared_ptr<Pattern>>(__patterns)) {

        for (auto& job_path: job_paths) {
            std::shared_ptr<Core::FileSpooler> file_spooler(new Core::FileSpooler(job_path.c_str(), ".sjob", __job_queue));
            __file_spoolers.push_back(file_spooler);
        }
        
        for (int i = 0; i < sorter_count; ++i) {
            std::shared_ptr<Sorter> sorter(new Sorter(__pattern_matching_machine, __job_queue));
            __sorters.push_back(sorter);
        }
    }
    
    SortingMachine::~SortingMachine() { }
    
    void 
    SortingMachine::start() {
        for (auto& file_spooler: __file_spoolers) {
            std::thread thread(&Core::FileSpooler::start, file_spooler);
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
            (*spooler).stop();
        }
        for (auto& sorter: __sorters) {
            (*sorter).stop();
        }
    }
    
} /* namespace Sorter */
