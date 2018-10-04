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

#include "Pattern.h"
#include "PatternFileReader.h"
#include "PatternMatcher/PatternMatchingMachine.h"
#include "PatternMatcher/IPattern.h"
#include "PatternMatcher/IPatternReader.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    if (argc < 3)
    {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
    
    Sorter::PatternFileReader patternFileReader;
    std::set<PatternMatcher::IPattern> patterns(patternFileReader.read(argv[1]));
    PatternMatcher::PatternMatchingMachine pattern_matcher(patterns);
    
    for (auto& pattern: patterns)
    {
        std::cout << pattern;
    }
    
    return 0;
}

