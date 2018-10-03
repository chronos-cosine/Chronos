/* 
 * File:   Pattern.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include "Pattern.hpp"

namespace Sorter 
{

Pattern::~Pattern() { }
 
Pattern::Pattern(const unsigned long long& id, 
            const std::string& pattern,
            Bin* bin)
    : __id(id), PatternMatcher::Pattern(pattern)
{
    __bin = bin;
}

Pattern::Pattern(const Pattern& orig)
    : __id(orig.__id), PatternMatcher::Pattern(orig)
{ 
    __bin = orig.get_bin();
}
    
const unsigned long long& 
Pattern::get_id() const
{
    return __id;
}

unsigned long long 
Pattern::get_id()
{
    return __id;
}

const Bin* 
Pattern::get_bin() const
{
    return __bin;
}

Bin* 
Pattern::get_bin()
{
    return __bin;
}

//Operators 
Pattern& 
Pattern::operator=(const Pattern& rhs)
{
    __id = rhs.get_id();
    __pattern = rhs.get_value();
}

bool 
Pattern::operator==(const std::string& rhs) const
{
    return __pattern == rhs;
}

bool 
Pattern::operator!=(const std::string& rhs) const
{
    return __pattern != rhs;
}

bool 
Pattern::operator==(const unsigned long long& rhs)
{
    return __id == rhs;
}

bool 
Pattern::operator!=(const unsigned long long& rhs) const
{
    return __id != rhs;
}

bool 
Pattern::operator==(const Pattern& rhs) const
{
    return __id == rhs.get_id();
}

bool 
Pattern::operator!=(const Pattern& rhs) const
{
    return __id != rhs.get_id();
}

bool 
Pattern::operator<(const Pattern& rhs) const
{
    return __id < rhs.get_id();
}

} /* namespace Sorter */