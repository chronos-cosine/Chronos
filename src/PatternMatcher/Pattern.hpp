/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_PATTERN_HPP
#define PATTERNMATCHER_PATTERN_HPP

#include <boost/functional/hash.hpp>
#include <string>
#include <iostream>

namespace PatternMatcher
{

class Pattern {
public: 
    struct Hasher
    {
        std::size_t operator()(const Pattern& pattern) const
        {
            boost::hash<std::string> hash;
            return hash(pattern.get_value());
        }
    };
public:
    Pattern(const char* pattern);
    Pattern(const std::string& pattern);
    Pattern(const Pattern& orig);
    virtual ~Pattern();
    
    std::string::const_iterator begin();
    std::string::const_iterator end();
    const std::string& get_value() const;
    std::string& get_value();
    
    //Operators
    Pattern& operator=(const std::string& rhs);
    Pattern& operator=(const Pattern& rhs); 
    Pattern& operator=(const char* rhs); 
    bool operator==(const std::string& rhs) const;
    bool operator!=(const std::string& rhs) const;
    bool operator==(const Pattern& rhs) const;
    bool operator!=(const Pattern& rhs) const;
    bool operator<(const Pattern& rhs) const; 
protected:
    std::string __pattern;
};
 
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERN_HPP */

