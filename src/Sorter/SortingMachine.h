/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 19 November 2018, 11:14 AM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "Sorter/Models/Job.h"

#include <experimental/filesystem>
#include <vector>
#include <thread>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    
    class SortingMachine {
    public:
        virtual ~SortingMachine() = default; 
        SortingMachine(const std::vector<fs::path>& paths, 
                       const std::chrono::seconds& sleep_time);
    public:
        void start();
        void stop();
    private:
        void initialise_producers(const std::vector<fs::path>& paths,
                const std::chrono::seconds& sleep_time);
        void initialise_consumers();
    private:
        std::shared_ptr<Collections::ICollection<Sorter::Models::Job>> collection;
        std::vector<File::Spooler<Sorter::Models::Job>> producers;
        std::vector<std::thread> producer_threads;
        
    }; /* class SortingMachine */ 
    
} /* namespace Sorter */

    

#endif /* SORTER_SORTINGMACHINE_H */

