/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.cpp
 * Author: user
 * 
 * Created on 19 November 2018, 11:14 AM
 */

#include "Collections/Concurrent/Queue.h"
#include "SortingMachine.h"
#include "Sorter/Models/Job.h"

#include <chrono>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    
    SortingMachine::SortingMachine(const std::vector<fs::path>& paths, 
                       const std::chrono::seconds& sleep_time) 
      : Processors::ProcessorBase(sleep_time), 
        collection(std::make_shared<
            Collections::Concurrent::Queue<Sorter::Models::Job>>()) {
        initialise_producers(paths, sleep_time);
    }
    
    void 
    SortingMachine::initialise_producers(const std::vector<fs::path>& paths, 
            const std::chrono::seconds& sleep_time) {
        for (auto& path: paths) {
            File::Spooler<Sorter::Models::Job> producer(path, 
                    ".sjob", ".sdone", sleep_time, collection);
            producers.push_back(std::move(producer));
        }
    }
    
    bool 
    SortingMachine::process() {
        return false;
    }
    
} /* namespace Sorter */
