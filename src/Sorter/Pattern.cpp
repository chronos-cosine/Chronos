/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.cpp
 * Author: user
 * 
 * Created on 04 October 2018, 9:17 AM
 */

#include "Pattern.h"
#include "PatternMatcher/IPattern.h"

namespace Sorter {

    //constructors
    Pattern::Pattern(const unsigned long long& id, const char* value)
        : PatternMatcher::IPattern(value), __id(id)
    { }

    Pattern::Pattern(const unsigned long long& id, const std::string& value)
        : PatternMatcher::IPattern(value), __id(id)
    { }

    Pattern::Pattern(const Pattern& orig)
        : PatternMatcher::IPattern(orig), __id(orig.__id)
    { }

    Pattern::~Pattern()
    { }

    //member functions
    const unsigned long long& 
    Pattern::get_id() const
    {
        return __id;
    }

    //operators
    bool 
    Pattern::operator==(const Pattern& rhs) const
    {
        return __id == rhs.__id;
    }

    bool 
    Pattern::operator!=(const Pattern& rhs) const
    {
        return __id != rhs.__id;
    }

    bool 
    Pattern::operator<(const Pattern& rhs) const
    {
        return __id < rhs.__id;
    }

    bool 
    Pattern::operator>(const Pattern& rhs) const
    {
        return __id > rhs.__id;
    }

    //friend operators
    std::ostream& 
    operator<<(std::ostream& lhs, const Pattern& rhs)
    {
        lhs << "{\"Id\":\"" << rhs.__id
            << "\",\"Value\":\"" << rhs.get_value()
            << "\"}" << std::endl;
    }

} /* namespace Sorter */