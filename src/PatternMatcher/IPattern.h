/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IPattern.h
 * Author: user
 *
 * Created on 04 October 2018, 7:11 AM
 */

#ifndef PATTERNMATCHER_IPATTERN_H
#define PATTERNMATCHER_IPATTERN_H

#include <string>

class IPattern {
public:
    virtual ~IPattern() = 0; 
    
    std::string::iterator begin() = 0 noexcept;
    std::string::const_iterator begin() const = 0 noexcept;
    
    std::string::iterator end() = 0 noexcept;
    std::string::const_iterator end() const = 0 noexcept; 
};

#endif /* PATTERNMATCHER_IPATTERN_H */

