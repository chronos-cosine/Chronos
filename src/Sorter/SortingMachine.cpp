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

#include "SortingMachine.h"

namespace Sorter {
    
    SortingMachine::SortingMachine(const std::vector<fs::path>& paths, 
                       const std::chrono::seconds& sleep_time) 
    {
        initialise(paths);
    }
    
    void 
    SortingMachine::initialise_spoolers(const std::vector<fs::path>& paths) {
        
    }
    
} /* namespace Sorter */
