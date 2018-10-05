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

namespace Sorter {

    class Sorter {
    public:
        Sorter(char* pattern_file, char* bin_file);
        virtual ~Sorter();
    private:
        void link_pattern_bin();
    private:
        PatternFileReader __pattern_file_reader;
        BinFileReader __bin_file_reader;
        MemoryManagement __memory_management;
        std::set<Bin*> __bins;
        std::set<PatternMatcher::IPattern*> __patterns;
        PatternMatcher::PatternMatchingMachine __pattern_matching_machine;
    };

} /* namespace Sorter */

#endif /* SORTER_SORTER_H */

