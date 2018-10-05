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
 
#include "PatternMatcher/IPattern.h"
#include "Sorter/PatternFileReader.h"
#include "Sorter/BinFileReader.h"
#include "Sorter/Pattern.h"

/*
 * 
 */
int main(int argc, char** argv) {
    
    if (argc < 3)
    {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
    
    Sorter::PatternFileReader pattern_file_reader;
    Sorter::BinFileReader bin_file_reader;
    std::set<PatternMatcher::IPattern*> patterns(pattern_file_reader.read(argv[1]));
    std::set<Sorter::Bin*> bins(bin_file_reader.read(argv[2]));
    
    for (auto& p: patterns)
    {
        std::cout << *dynamic_cast<Sorter::Pattern*>(p) << std::endl;
    }
    for (auto& b: bins)
    {
        std::cout << *b << std::endl;
    }
         
    return 0;
}

