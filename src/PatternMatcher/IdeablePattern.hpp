/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IdeablePattern.hpp
 * Author: user
 *
 * Created on 21 September 2018, 2:36 PM
 */

#ifndef PATTERNMATCHER_IDEABLEPATTERN_HPP
#define PATTERNMATCHER_IDEABLEPATTERN_HPP

#include <string>
#include "Pattern.hpp"
 
namespace PatternMatcher
{

class IdeablePattern : public Pattern {
public:
    IdeablePattern(const long& id, const std::string& pattern); 
    virtual ~IdeablePattern();
    
    const long get_id() const;
    long get_id();
    
    IdeablePattern& operator=(const IdeablePattern& rhs); 
    bool operator==(const IdeablePattern& rhs);
    bool operator!=(const IdeablePattern& rhs);
    bool operator<(const IdeablePattern& rhs) const;
    
    friend std::ostream& operator<<(std::ostream& stream, IdeablePattern& pattern)
    {
       return stream << "{\"id\":\"" 
                     << pattern.get_id()
                     << "\", \"pattern\":\""
                     << pattern.get_value()
                     << "\"}";
    }
private:
    long __id;
};

} /* namespace PatternMatcher */
#endif /* PATTERNMATCHER_IDEABLEPATTERN_HPP */

