/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Chronos-Sorter.cpp
 * Author: user
 *
 * Created on 04 October 2018, 7:08 AM
 */

#include <iostream>
#include <set>
 
#include "Bin.h"
#include "MemoryManagement.h" 
#include "Pattern.h"
#include "PatternFileReader.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "PatternMatcher/IPattern.h"
#include "PatternMatcher/IPatternReader.h"
#include "BinFileReader.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    if (argc < 3)
    {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
     
    Sorter::BinFileReader binFileReader;
    std::map<unsigned long long, Sorter::Bin*> bins(binFileReader.read(argv[2]));
    Sorter::MemoryManagement memory_management;
    Sorter::PatternFileReader patternFileReader(&bins);
    
    std::set<PatternMatcher::IPattern*> patterns(patternFileReader.read(argv[1]));
    PatternMatcher::PatternMatchingMachine pattern_matcher(patterns);
    
    std::cout << "<PATTERNS>" << std::endl;
    for (auto* p: patterns)
    {  
        std::cout << *dynamic_cast<Sorter::Pattern*>(p) << std::endl;
    }
    
    std::cout << "<BINS>" << std::endl;
    for (auto& b: bins)
    { 
        std::cout << *b.second << std::endl;
    }
         
    return 0;
}

