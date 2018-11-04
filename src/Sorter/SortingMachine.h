/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter/SortingMachine.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 30 October 2018, 1:13 PM
 */

#ifndef SORTER_SORTINGMACHINE_H
#define SORTER_SORTINGMACHINE_H

#include "Collections/ICollection.h"
#include "File/Spooler.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Processors/ProcessorBase.h"
#include "Sorter/Bin.h"
#include "Sorter/Job.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"
#include "Sorter/Settings.h"

#include <map>
#include <set>
#include <string>
#include <sstream>
#include <thread>

namespace Sorter {
    
    class SortingMachine : public Processors::ProcessorBase,
                           public Notifier::Notifiable {
        SortingMachine(const SortingMachine&) = delete;
        SortingMachine& operator=(const SortingMachine&) = delete;
    public:
        virtual ~SortingMachine();
        SortingMachine(const std::shared_ptr<Settings>& settings);
        SortingMachine(const std::shared_ptr<Settings>& settings, 
                       const std::shared_ptr<Notifier::NotifierBase>& notifier);
        
        virtual void start();
        virtual void stop();
    protected:
        virtual bool process();
    private:
        void initialise();
        bool is_boolean_match(const Job& input);
        bool is_bin_hierarchy_match(const Job& input);
        void initialise_bins(const std::vector<Bin>& bins);
        void initialise_patterns(const std::vector<Pattern>& patterns);
        void initialise_spoolers();
        void initialise_sorters(); 
        void initialise_matcher(const std::vector<Pattern>& patterns);
        void reset_job_directory();
    private:
        std::map<unsigned long long, Pattern> __patterns;
        std::map<unsigned long long, Bin> __bins; 
        std::map<unsigned long long, std::map<BooleanOperator, std::set<Pattern>>> __bin_patterns;
        std::shared_ptr<Settings> __settings;
        std::map<Job, std::map<unsigned long long, std::set<Pattern>>> __pattern_matches;
        std::map<Job, std::set<Bin>> __bin_matches;
        std::shared_ptr<Collections::ICollection<std::string>> __jobs;
        std::stringstream __ss_notification;
        std::shared_ptr<PatternMatcher::PatternMatchingMachine<Job, Pattern, Sorter>> __matcher;
        std::vector<std::shared_ptr<File::Spooler>> __spoolers;
        std::vector<std::shared_ptr<Sorter>> __sorters;
        std::vector<std::thread> __spooler_threads;
        std::vector<std::thread> __sorter_threads;
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
        
    }; /* class SortingMachine */
    
} /* namespace Sorter */


#endif /* SORTER_SORTINGMACHINE_H */

