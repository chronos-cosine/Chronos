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

#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Sorter.h"
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
        SortingMachine(std::shared_ptr<Settings> settings);
    private:
        void initialise();
    private:
        std::map<unsigned long long, Pattern> __patterns;
        std::map<unsigned long long, Bin> __bins;
        std::map<unsigned long long, std::set<Pattern*>> __bin_patterns;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>> __matcher;
        std::shared_ptr<Settings> __settings;
        std::map<Job, std::set<Pattern>> __matches;
    private:
        struct completed {
            SortingMachine* sorting_machine;
            
            completed(SortingMachine* sm); 
            void operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& total_matches);
        };
        struct match_found {
            SortingMachine* sorting_machine;
            
            match_found(SortingMachine* sm);
            void operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& position,
                const std::set<Pattern>& patterns);
        };
        completed __completed;
        match_found __match_found;
        
    }; /* class SortingMachine */
    
} /* namespace Sorter */


#endif /* SORTER_SORTINGMACHINE_H */

