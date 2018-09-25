/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CompletedSignalArgs.hpp
 * Author: user
 *
 * Created on 21 September 2018, 9:53 AM
 */

#ifndef PATTERNMATCHER_COMPLETEDSIGNALARGS_HPP
#define PATTERNMATCHER_COMPLETEDSIGNALARGS_HPP

#include <string>

namespace PatternMatcher
{
 
class CompletedSignalArgs {
public:
    CompletedSignalArgs(const int& patterns_found, 
                        const std::string& input);
    virtual ~CompletedSignalArgs();
    
    const int get_patterns_found() const;
    int get_patterns_found();
    
    const std::string& get_input() const;
    std::string& get_input();
private:
    int __patterns_found;
    std::string __input;
};

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_COMPLETEDSIGNALARGS_HPP */

