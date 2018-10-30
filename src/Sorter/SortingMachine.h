/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortingMachine.h
 * Author: user
 *
 * Created on 30 October 2018, 1:13 PM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Sorter/Bin.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings.h"

#include <map>
#include <set>

namespace Sorter {
    
    class SortingMachine {
        SortingMachine(const SortingMachine&) = delete;
        SortingMachine& operator=(const SortingMachine&) = delete;
    public:
        virtual ~SortingMachine();
        SortingMachine(Settings* settings);
    private:
        void initialise();
    private:
        Settings* __settings;
        std::map<unsigned long long, Pattern> __patterns;
        std::map<unsigned long long, Bin> __bins;
        std::map<unsigned long long, std::set<Pattern*>> __bin_patterns;
        
    }; /* class SortingMachine */
    
} /* namespace Sorter */


#endif /* SORTER_SORTINGMACHINE_H */

