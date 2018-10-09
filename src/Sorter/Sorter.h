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


#include "Core/IProcessor.h"
#include "PatternMatcher/IPattern.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "Sorter/Bin.h"
#include "Sorter/BinFileReader.h"
#include "Sorter/MemoryManagement.h"
#include "Sorter/Pattern.h"
#include "Sorter/PatternFileReader.h"

#include <iostream>
#include <map>
#include <set>
#include <string>

namespace Sorter {

    class Sorter : public Core::IProcessor {
    private:
        struct completed_functor {
            Sorter* __sorter;
            void operator()(void* sender, 
                            const unsigned long long& total_matches,
                            PatternMatcher::IPattern* input) const {
                std::cout << "Input: " << std::endl << *input 
                          << " found : " << total_matches 
                          << " matchers.  These include: " << std::endl;
                for (auto& pair: __sorter->__matches[input])
                {
                    std::cout << *(pair.first) << std::endl << "at positions: ";
                    for (const auto& position: __sorter->__matches[input][pair.first])
                    {
                        std::cout << position << ", ";
                    }
                    std::cout << "\b\b" << std::endl;
                }
                
                __sorter->__matches.erase(input);
            }
        };
        struct match_found_functor {
            Sorter* __sorter;
            void operator()(void* sender , 
                            const unsigned long long& position,
                            PatternMatcher::IPattern* input ,
                            const std::set<PatternMatcher::IPattern*>& patterns) const {
                for (PatternMatcher::IPattern* p: patterns) {
                    Pattern* pattern = dynamic_cast<Pattern*>(p); 
                    __sorter->__matches[input][pattern].insert(position);
                }
            }
        };
    public:
        Sorter(char* pattern_file, char* bin_file);
        Sorter(char* pattern_file, char* bin_file, Core::INotifier* notifier);
        virtual ~Sorter();
    private:
        void initialise_sorter();
        void link_pattern_bin();
        template <typename T> std::set<T*> map_values_to_set(const std::map<unsigned long long, T*> map);
    protected:
        virtual bool process();
    private:
        PatternFileReader __pattern_file_reader;
        BinFileReader __bin_file_reader;
        MemoryManagement __memory_management;
        std::map<unsigned long long, Bin*> __bins;
        std::map<unsigned long long, PatternMatcher::IPattern*> __patterns;
        PatternMatcher::PatternMatchingMachine __pattern_matching_machine;
        Sorter::completed_functor __completed_functor;
        Sorter::match_found_functor __match_found_functor;
        std::map<PatternMatcher::IPattern*, std::map<Pattern*, std::set<unsigned long long>>> __matches;
        
    }; /* class Sorter */
    
    template <typename T>
    std::set<T*>
    Sorter::map_values_to_set(const std::map<unsigned long long, T*> map) {
        std::set<T*> set;
        for (const auto& pair: map) {
            set.insert(pair.second);
        }
        
        return set;
    }
    
} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

