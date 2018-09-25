/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.cpp
 * Author: user
 * 
 * Created on 20 September 2018, 2:42 PM
 */

#include "Pattern.hpp"
 
namespace PatternMatcher
{
     
Pattern::Pattern(const std::string& pattern)
    : __pattern(pattern)
{ }

Pattern::Pattern(const Pattern& orig)
    : __pattern(orig.__pattern)
{ }

Pattern::~Pattern() { }

std::string::const_iterator 
Pattern::begin()
{
    return __pattern.begin();
}

std::string::const_iterator 
Pattern::end()
{
    return __pattern.end();
}

const std::string&
Pattern::get_value() const
{
    return __pattern;
}

std::string& 
Pattern::get_value()
{
    return __pattern;
}

Pattern& 
Pattern::operator=(const std::string& rhs)
{
    __pattern = rhs;
    return *this;
}

Pattern& 
Pattern::operator=(const Pattern& rhs)
{
    __pattern = rhs.__pattern;
    return *this;
}

bool 
Pattern::operator<(const Pattern& rhs) const
{
    return __pattern < rhs.__pattern;
}

bool 
Pattern::operator==(const Pattern& rhs)
{
    return __pattern == rhs.__pattern;
}

bool 
Pattern::operator!=(const Pattern& rhs)
{
    return __pattern != rhs.__pattern;
}

} /* namespace PatternMatcher */