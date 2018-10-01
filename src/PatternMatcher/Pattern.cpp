/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include "Pattern.hpp"
 
namespace PatternMatcher
{
     
Pattern::Pattern(const char* pattern)
    : __pattern(pattern)
{ }
     
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

Pattern& 
Pattern::operator=(const char* rhs)
{
    __pattern = rhs;
    return *this;
}

bool
Pattern::operator<(const Pattern& rhs) const
{
    return __pattern < rhs.__pattern;
}

bool 
Pattern::operator==(const Pattern& rhs) const
{
    return __pattern == rhs.__pattern;
}

bool 
Pattern::operator!=(const Pattern& rhs) const
{
    return __pattern != rhs.__pattern;
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

} /* namespace PatternMatcher */