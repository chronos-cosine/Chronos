/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IPatternReader.h
 * Author: user
 *
 * Created on 04 October 2018, 9:38 AM
 */

#ifndef PATTERNMATCHER_IPATTERNREADER_H
#define PATTERNMATCHER_IPATTERNREADER_H

#include <set>
#include "IPattern.h"

namespace PatternMatcher {
    
    class IPatternReader {
    public:
        virtual ~IPatternReader() { }; 
        virtual std::set<IPattern*> read(const char* path) = 0;
    }; /* class IPatternReader */
    
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_IPATTERNREADER_H */

