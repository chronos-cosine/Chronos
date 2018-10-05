/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinFileReader.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 2:48 PM
 */

#include "BinFileReader.h"

namespace Sorter {

    //constructors
    BinFileReader::BinFileReader()
    { }
    
    BinFileReader::~BinFileReader()
    { }

    //member functions
    std::set<Bin*> 
    BinFileReader::read(const char* path)
    {
        std::set<Bin*> bins;
        std::ifstream file(path);
        if (file)
        {
            std::string line;
            
            getline(file, line);
            char separator = get_separator(line);
            
            while (getline(file, line))
            {
                bins.insert(get_bin(line, separator, bins));
            }
        }
        file.close();
        
        return bins;
    }

    char 
    BinFileReader::get_separator(const std::string& line)
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
    
    Bin* 
    BinFileReader::get_bin(const std::string& line, 
                           const char& separator, 
                           const std::map<unsigned long long, Bin*> bins)
    {
        try {
            std::string id;
            std::string value;
            std::string parent_id;
            Bin* parent_bin = nullptr;
            
            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);
            getline(stream, parent_id, separator);
            if (parent_id.length() > 0)
            {
                parent_bin = *bins.find(std::stoull(id));
            }
            
            PatternMatcher::IPattern* obj = new Sorter::Pattern(std::stoull(id), value, parent_bin);
            return obj;
        } catch (const std::invalid_argument&)
        {
            std::cerr << std::endl << "ERROR: The line to read is not in the format <ID>" <<  separator << "<PATTERN>"
                      << std::endl << "Application will close..." << std::endl;
            exit(1);
        }
    }

} /* namespace Sorter */