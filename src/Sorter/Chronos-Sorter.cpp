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
#include <boost/filesystem.hpp>
#include <iostream>
#include <set>

#include "Core/Notifier_cout.h"
#include "Sorter/Sorter.h"
#include "Sorter/Pattern.h"

void
check_paths_valid(const char* pattern_file, const char* bin_file, const char* job_path)
{
    if (!boost::filesystem::exists(boost::filesystem::path(pattern_file)))
    {
        std::cerr << "Supplied pattern file does not exist.\nExiting..." << std::endl;
        exit(1);
    }
    
    if (!boost::filesystem::exists(boost::filesystem::path(bin_file)))
    {
        std::cerr << "Supplied bin file does not exist.\nExiting..." << std::endl;
        exit(1);
    }
    
    if (!boost::filesystem::exists(boost::filesystem::path(job_path)))
    {
        std::cerr << "Supplied job directory " << job_path 
                  << " does not exist.\nExiting..." << std::endl;
        exit(1);
    }
}

/*
 * 
 */
int main(int argc, char** argv) { 
    if (argc < 4) {
        std::cerr << "Incorrect number of parameters supplied" << std::endl;
        return 1;
    }
    check_paths_valid(argv[1], argv[2], argv[3]);
        
    Core::Notifier_cout notifier;
    Sorter::Sorter sorter(argv[1], argv[2], argv[3], &notifier);
    sorter.start();
             
    return 0;
}

