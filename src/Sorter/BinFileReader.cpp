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
#include <sstream>
#include <fstream>
#include <iostream>

namespace Sorter {

    //constructors
    BinFileReader::BinFileReader()
    { }
    
    BinFileReader::~BinFileReader()
    { }

    //member functions
    std::map<unsigned long long, Bin*>&
    BinFileReader::read(const char* path)
    { 
        std::ifstream file(path);
        if (file)
        {
            std::string line;
            
            getline(file, line);
            char separator = get_separator(line);
            
            while (getline(file, line))
            {
                Bin* bin = get_bin(line, separator);
                __bins[bin->get_id()] = bin;
            }
        }
        file.close();
        
        return __bins;
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
    BinFileReader::get_parent_bin(const unsigned long long& parent_id)
    {
        std::map<unsigned long long, Bin*>::const_iterator b = __bins.find(parent_id);
        if (b != __bins.end())
        { 
            return b->second;
        }
        else 
        {
            return nullptr;
        }
    }
    
    Bin* 
    BinFileReader::get_bin(const std::string& line, 
                           const char& separator)
    {
        try {
            std::string id;
            std::string value;
            std::string parent_id;
            
            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);
            getline(stream, parent_id, separator); 
            
            Sorter::Bin* obj = new Sorter::Bin(std::stoull(id), value, get_parent_bin(std::stoull(parent_id)));
            __bins[obj->get_id()] = obj;
            
            return obj;
        } catch (const std::invalid_argument&)
        {
            std::cerr << std::endl << "ERROR: The line to read is not in the format " 
                      << "<ID>" <<  separator << "<BIN NAME>" <<  separator << "<PARENT ID>"
                      << std::endl << "Application will close..." << std::endl;
            exit(1);
        }
    }

} /* namespace Sorter */