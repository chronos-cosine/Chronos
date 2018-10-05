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
    Pattern::Pattern(const unsigned long long& id, 
                     const char* value,
                     Bin* bin)
        : PatternMatcher::IPattern(value), __id(id), __bin(bin)
    { }

    Pattern::Pattern(const unsigned long long& id, 
                     const std::string& value,
                     Bin* bin)
        : PatternMatcher::IPattern(value), __id(id), __bin(bin)
    { }

    Pattern::Pattern(const Pattern& orig)
        : PatternMatcher::IPattern(orig), __id(orig.__id), __bin(orig.__bin)
    { }

    Pattern::~Pattern()
    { }

    //member functions
    const unsigned long long& 
    Pattern::get_id() const
    {
        return __id;
    }
    
    Bin* 
    Pattern::get_bin() const
    {
        return __bin;
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
            << "\",\"Bin\":";
        
        if (nullptr == rhs.__bin)
        {
            lhs << "null";
        }
        else 
        {
            lhs << *rhs.__bin;
        }
        lhs << "}";
        return lhs;
    }

} /* namespace Sorter */
