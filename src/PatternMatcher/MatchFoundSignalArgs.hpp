/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatchFoundSignalArgs.hpp
 * Author: user
 *
 * Created on 21 September 2018, 10:10 AM
 */

#ifndef PATTERNMATCHER_MATCHFOUNDSIGNALARGS_HPP
#define PATTERNMATCHER_MATCHFOUNDSIGNALARGS_HPP

#include <set>
#include <string>

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class MatchFoundSignalArgs {
public:
    MatchFoundSignalArgs(int position, 
                         const std::string& input,
                         std::set<PATTERN_TYPE>* patterns); 
    virtual ~MatchFoundSignalArgs();
    
    const int get_position() const;
    int get_position();
    
    const std::string& get_input() const;
    std::string& get_input();
    
    const std::set<PATTERN_TYPE>* get_patterns() const;
    std::set<PATTERN_TYPE>* get_patterns();
private:
    int __position;
    std::string __input;
    std::set<PATTERN_TYPE>* __patterns;
};


} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_MATCHFOUNDSIGNALARGS_HPP */

