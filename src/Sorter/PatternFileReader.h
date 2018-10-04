/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternFileReader.h
 * Author: user
 *
 * Created on 04 October 2018, 9:48 AM
 */

#ifndef SORTER_PATTERNFILEREADER_H
#define SORTER_PATTERNFILEREADER_H
 
#include "PatternMatcher/IPattern.h"
#include "PatternMatcher/IPatternReader.h"
#include <set>
#include <sstream>

namespace Sorter {
    class PatternFileReader : public PatternMatcher::IPatternReader {
    public:
        //constructors
        PatternFileReader(); 
        virtual ~PatternFileReader();
        
        //member functions
        virtual std::set<PatternMatcher::IPattern> read(const char* path);
    private:
        char get_separator(const std::string& line);
        PatternMatcher::IPattern get_pattern(const std::string& line, const char& separator);
    }; /* class PatternFileReader */ 
} /* namespace Sorter */

#endif /* SORTER_PATTERNFILEREADER_H */

