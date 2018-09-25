/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pattern.hpp
 * Author: user
 *
 * Created on 20 September 2018, 2:42 PM
 */

#ifndef PATTERNMATCHER_PATTERN_HPP
#define PATTERNMATCHER_PATTERN_HPP

#include <string>
#include <iostream>

namespace PatternMatcher
{

class Pattern {
public:
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
    bool operator==(const Pattern& rhs);
    bool operator!=(const Pattern& rhs);
    bool operator<(const Pattern& rhs) const;
    
    friend std::ostream& operator<<(std::ostream& stream, Pattern& pattern)
    {
        stream << pattern.get_value();

        return stream;
    }
protected:
    std::string __pattern;
};
 
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERN_HPP */

