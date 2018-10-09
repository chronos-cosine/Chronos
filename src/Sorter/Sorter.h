/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sorter.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef SORTER_SORTER_H
#define SORTER_SORTER_H

#include "PatternMatcher/IPattern.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/PatternFileReader.h"
#include "Sorter/BinFileReader.h"
#include "Sorter/MemoryManagement.h"
#include "Sorter/Bin.h"

#include <string>
#include <set>
#include <map>

namespace Sorter {

    class Sorter {
    private:
        struct completed_functor {
            Sorter* __sorter;
            void operator()(void* sender, 
                 const unsigned long long& total_matches,
                 PatternMatcher::IPattern* input)
            {
                
            }
        };
        struct match_found_functor {
            Sorter* __sorter;
            void operator()(void* sender , 
                 const unsigned long long& position,
                 PatternMatcher::IPattern* input ,
                 const std::set<PatternMatcher::IPattern*>& patterns)
            {
                
            }
        };
    public:
        Sorter(char* pattern_file, char* bin_file);
        virtual ~Sorter();
    private:
        void link_pattern_bin();
        template <typename T>
        std::set<T*> map_values_to_set(const std::map<unsigned long long, T*> map);
    private:
        PatternFileReader __pattern_file_reader;
        BinFileReader __bin_file_reader;
        MemoryManagement __memory_management;
        std::map<unsigned long long, Bin*> __bins;
        std::map<unsigned long long, PatternMatcher::IPattern*> __patterns;
        PatternMatcher::PatternMatchingMachine __pattern_matching_machine;
        Sorter::completed_functor __completed_functor;
        Sorter::match_found_functor __match_found_functor;
    };
    
    template <typename T>
    std::set<T*>
    Sorter::map_values_to_set(const std::map<unsigned long long, T*> map)
    {
        std::set<T*> set;
        for (const auto& pair: map)
        {
            set.insert(pair.second);
        }
        
        return set;
    }
    
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

