/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CompletedSignalArgs.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 9:53 AM
 */

#include "CompletedSignalArgs.hpp"

namespace PatternMatcher
{

CompletedSignalArgs::CompletedSignalArgs(const int& patterns_found, 
        const std::string& input)
    : __patterns_found(patterns_found), __input(input)
{ }
 
CompletedSignalArgs::~CompletedSignalArgs() 
{ }

const int 
CompletedSignalArgs::get_patterns_found() const
{
    return __patterns_found;
}

int 
CompletedSignalArgs::get_patterns_found()
{
    return __patterns_found;
}

const std::string& 
CompletedSignalArgs::get_input() const
{
    return __input;
}

std::string&
CompletedSignalArgs::get_input()
{
    return __input;
}

} /* namespace PatternMatcher */

