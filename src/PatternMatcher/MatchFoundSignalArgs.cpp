/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatchFoundSignalArgs.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 10:10 AM
 */

#include "MatchFoundSignalArgs.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
MatchFoundSignalArgs<PATTERN_TYPE>::MatchFoundSignalArgs(int position, const std::string& input, std::set<PATTERN_TYPE>* patterns) 
    : __position(position), __input(input)
{ 
    __patterns = patterns;
}
 
template <typename PATTERN_TYPE>
MatchFoundSignalArgs<PATTERN_TYPE>::~MatchFoundSignalArgs() 
{ }

template <typename PATTERN_TYPE>
const int 
MatchFoundSignalArgs<PATTERN_TYPE>::get_position() const
{
    return __position;
}

template <typename PATTERN_TYPE>
int 
MatchFoundSignalArgs<PATTERN_TYPE>::get_position()
{
    return __position;
}

template <typename PATTERN_TYPE>
const std::string& 
MatchFoundSignalArgs<PATTERN_TYPE>::get_input() const
{
    return __input;
}

template <typename PATTERN_TYPE>
std::string& 
MatchFoundSignalArgs<PATTERN_TYPE>::get_input()
{
    return __input;
}

template <typename PATTERN_TYPE>
const std::set<PATTERN_TYPE>* 
MatchFoundSignalArgs<PATTERN_TYPE>::get_patterns() const
{
    return __patterns;
}

template <typename PATTERN_TYPE>
std::set<PATTERN_TYPE>* 
MatchFoundSignalArgs<PATTERN_TYPE>::get_patterns()
{
    return __patterns;
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class MatchFoundSignalArgs<Pattern>;

} /* namespace PatternMatcher */

