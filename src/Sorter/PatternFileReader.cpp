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

#include "PatternMatcher/IPattern.h"
#include "Sorter/PatternFileReader.h"
#include "Sorter/Pattern.h" 
#include "Sorter/Bin.h"

#include <exception>
#include <sstream>
#include <string>

namespace Sorter {
    
    PatternFileReader::PatternFileReader()
    { }
    
    PatternFileReader::~PatternFileReader()
    { }

    bool 
    PatternFileReader::read_line(const std::string& line, 
                                 const char& separator,
                                 PatternMatcher::IPattern** pattern)
    {
        try {
            std::string id;
            std::string value;
            std::string bin_id;

            std::istringstream stream(line);
            getline(stream, id, separator);
            getline(stream, value, separator);
            getline(stream, bin_id, separator); 

            *pattern = dynamic_cast<PatternMatcher::IPattern*>(new Pattern(std::stoull(id), value, std::stoull(bin_id)));
        } catch (const std::exception&)
        {
            return false;
        }
        
        return true;
    }

} /* namespace Sorter */
