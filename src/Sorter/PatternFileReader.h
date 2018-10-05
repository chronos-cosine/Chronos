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

#include "Core/ICsvFileReader.h"
#include "PatternMatcher/IPattern.h"

namespace Sorter {
    class PatternFileReader : public Core::ICsvFileReader<PatternMatcher::IPattern> {
    public: 
        PatternFileReader();
        virtual ~PatternFileReader();
        virtual bool read_line(const std::string& line, 
                               const char& separator,
                               PatternMatcher::IPattern** pattern);
    }; /* class PatternFileReader */ 
} /* namespace Sorter */

#endif /* SORTER_PATTERNFILEREADER_H */

