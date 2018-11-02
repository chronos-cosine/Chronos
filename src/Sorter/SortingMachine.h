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

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings.h"

#include <map>
#include <set>
#include <string>
#include <sstream>

namespace Sorter {
    
    class SortingMachine {
        SortingMachine(const SortingMachine&) = delete;
        SortingMachine& operator=(const SortingMachine&) = delete;
        
    public:
        virtual ~SortingMachine();
        SortingMachine(const std::shared_ptr<Settings>& settings);
        SortingMachine(const std::shared_ptr<Settings>& settings, std::shared_ptr<Notifier::INotifier> __notifier);
    private:
        void initialise();
        bool is_boolean_match(const Job& input);
        bool is_bin_hierarchy_match(const Job& input);
    private:
        std::map<unsigned long long, Pattern> __patterns;
        std::map<unsigned long long, Bin> __bins; 
        std::map<unsigned long long, std::map<BooleanOperator, std::set<Pattern>>> __bin_patterns;
        std::shared_ptr<Settings> __settings;
        std::map<Job, std::map<unsigned long long, std::set<Pattern>>> __pattern_matches;
        std::map<Job, std::set<Bin>> __bin_matches;
        std::shared_ptr<Collections::ICollection<std::string>> __jobs;
        std::shared_ptr<Notifier::INotifier> __notifier;
        std::stringstream __ss_notification;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>> __matcher;
        std::vector<std::unique_ptr<File::Spooler>> __spoolers;
        std::vector<std::unique_ptr<Sorter>> __sorters;
    private:
        struct completed {
            SortingMachine* sorting_machine;
            
            completed(SortingMachine* sm); 
            void operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& total_matches);
        }; /* struct completed */
        struct match_found {
            SortingMachine* sorting_machine;
            
            match_found(SortingMachine* sm);
            void operator()(Sorter* sender, 
                const Job& input,
                const unsigned long long& position,
                const std::set<Pattern>& patterns);
        }; /* struct match_found */
        completed __completed;
        match_found __match_found;
        void notify(const std::string& message);
        void notify(std::stringstream& message);
    }; /* class SortingMachine */
    
} /* namespace Sorter */


#endif /* SORTER_SORTINGMACHINE_H */

