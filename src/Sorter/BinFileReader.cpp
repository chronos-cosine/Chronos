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

#include "Sorter/BinFileReader.h"
#include "Sorter/Bin.h" 

#include <sstream>  

namespace Sorter {
    
    BinFileReader::BinFileReader() { }
    
    BinFileReader::~BinFileReader() { }

    std::set<Sorter::Bin*> 
    BinFileReader::read(const char* filename) {
        __added.clear();
        return Core::ICsvFileReader<Sorter::Bin>::read(filename);
    }
    
    bool 
    BinFileReader::read_line(const std::string& line, 
                                 const char& separator,
                                 Sorter::Bin** bin) {
        try {
            std::string id;
            std::string value;
            std::string parent_id;

            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);
            getline(stream, parent_id, separator); 

            unsigned long long ulong_id = std::stoull(id); 
            if (__added.find(ulong_id) == __added.end())
            {
                *bin = new Sorter::Bin(ulong_id, value, std::stoull(parent_id));;
            }
        } 
        catch (const std::exception&) {
            return false;
        }
        
        return true;
    }

} /* namespace Sorter */