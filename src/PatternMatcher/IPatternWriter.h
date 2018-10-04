/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IPatternWriter.h
 * Author: user
 *
 * Created on 04 October 2018, 9:38 AM
 */

#ifndef PATTERNMATCHER_IPATTERNWRITER_H
#define PATTERNMATCHER_IPATTERNWRITER_H

#include <set>
#include "IPattern.h"

namespace PatternMatcher {
    
    class IPatternWriter {
    public:
        virtual ~IPatternWriter() { };
        virtual void write(const std::set<IPattern>& patterns) = 0;
    }; /* class IPatternWriter */
    
} /* namespace PatternMatcher */

#endif /* SORTER_IPATTERNWRITER_H */

