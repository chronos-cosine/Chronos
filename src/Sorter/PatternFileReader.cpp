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
#include "Sorter/Bin.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <map>

namespace Sorter {
    
    //constructors
    PatternFileReader::PatternFileReader(std::map<unsigned long long, Bin*>* bins)
        : __bins(bins)
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
    
    Sorter::Bin*
    PatternFileReader::get_bin(const unsigned long long& bin_id)
    {
        std::map<unsigned long long, Bin*>::iterator bin_iterator = __bins->find(bin_id);
        if (bin_iterator != __bins->end())
        {
            return bin_iterator->second;
        }
        else 
        {
            return nullptr;
        }
    }
    
    PatternMatcher::IPattern*
    PatternFileReader::get_pattern(const std::string& line, const char& separator)
    {
        try {
            std::string id;
            std::string value;
            std::string bin_id;
            Bin* bin = nullptr;
            
            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);
            getline(stream, bin_id, separator); 

            PatternMatcher::IPattern* obj = new Sorter::Pattern(std::stoull(id), value, get_bin(std::stoull(bin_id)));
            
            return obj;
        } catch (const std::invalid_argument&)
        {
            std::cerr << std::endl << "ERROR: The line to read is not in the format <ID>" <<  separator << "<PATTERN>"
                      << std::endl << "Application will close..." << std::endl;
            exit(1);
        }
    }

    //member functions
    std::set<PatternMatcher::IPattern*>
    PatternFileReader::read(const char* path)
    {
        std::set<PatternMatcher::IPattern*> patterns;
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