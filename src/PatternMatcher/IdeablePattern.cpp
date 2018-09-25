/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IdeablePattern.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 2:36 PM
 */

#include "IdeablePattern.hpp"

namespace PatternMatcher
{
  
IdeablePattern::~IdeablePattern() 
{ }

IdeablePattern::IdeablePattern(const long& id, const std::string& pattern)
    : Pattern(pattern), __id(id)
{ }
    
const long 
IdeablePattern::get_id() const
{
    return __id;
}

long 
IdeablePattern::get_id()
{
    return __id;
}

IdeablePattern& 
IdeablePattern::operator=(const IdeablePattern& rhs)
{
    __pattern = rhs.get_value();
    __id = rhs.__id;
    return *this;
}

bool 
IdeablePattern::operator==(const IdeablePattern& rhs)
{
    return __id == rhs.__id;
}

bool 
IdeablePattern::operator!=(const IdeablePattern& rhs)
{
    return __id != rhs.__id;
}

bool 
IdeablePattern::operator<(const IdeablePattern& rhs) const
{
    return __id < rhs.__id;
}
  
} /* namespace PatternMatcher */