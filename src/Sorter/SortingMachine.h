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

#include "File/Spooler.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Models/Job.h"

#include <experimental/filesystem>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace Sorter {
    
    class SortingMachine : public Processors::ProcessorBase {
    public:
        virtual ~SortingMachine() = default; 
        SortingMachine(const std::vector<fs::path>& paths, 
                       const std::chrono::seconds& sleep_time);
    private:
        void initialise_spoolers(const std::vector<fs::path>& paths);
    private:
        std::vector<std::shared_ptr<File::Spooler<Sorter::Models::Job>>> producers;
        
    }; /* class SortingMachine */ 
    
} /* namespace Sorter */

    

#endif /* SORTER_SORTINGMACHINE_H */

