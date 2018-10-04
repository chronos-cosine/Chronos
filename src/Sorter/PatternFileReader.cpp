/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternFileReader.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 9:48 AM
 */

#include "PatternFileReader.h"
#include "PatternMatcher/IPattern.h"
#include "Sorter/Pattern.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>

namespace Sorter {
    
    //constructors
    PatternFileReader::PatternFileReader()
    { }
    
    PatternFileReader::~PatternFileReader()
    { }
    
    char 
    PatternFileReader::get_separator(const std::string& line)
    {
        if (line.length() != 5
            || line.find("sep=") == std::string::npos)
        {
            std::cerr << std::endl << "ERROR: The first line of the Pattern file must specify the separator to use." 
                      << std::endl << "sep=<SEPARATOR> where <SEPARATOR> is a character to separate with. Example of a first line:" << std::endl
                      << "sep=," << std::endl << std::endl;
            exit(1);
        }
        return line[4];
    }
    
    PatternMatcher::IPattern 
    PatternFileReader::get_pattern(const std::string& line, const char& separator)
    {
        try {
            std::string id;
            std::string value;
            
            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);

            return Sorter::Pattern(std::stoull(id), value);
        } catch (const std::invalid_argument&)
        {
            std::cerr << std::endl << "ERROR: The line to read is not in the format <ID>" <<  separator << "<PATTERN>"
                      << std::endl << "Application will close..." << std::endl;
            exit(1);
        }
    }

    //member functions
    std::set<PatternMatcher::IPattern>
    PatternFileReader::read(const char* path)
    {
        std::set<PatternMatcher::IPattern> patterns;
        std::ifstream file(path);
        if (file)
        {
            std::string line;
            
            getline(file, line);
            char separator = get_separator(line);
            
            while (getline(file, line))
            {
                patterns.insert(get_pattern(line, separator));
            }
        }
        file.close();
        
        return patterns;
    }

} /* namespace Sorter */
