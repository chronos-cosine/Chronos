/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Input.cpp
 * Author: user
 * 
 * Created on 25 September 2018, 2:52 PM
 */

#include "Input.hpp" 

namespace PatternMatcher
{
     
Input::Input(const std::string& input)
    : __input(input)
{ }

Input::Input(const Input& orig)
    : __input(orig.__input)
{ }

Input::~Input() { }

std::string::const_iterator 
Input::begin()
{
    return __input.begin();
}

std::string::const_iterator 
Input::end()
{
    return __input.end();
}

const std::string&
Input::get_value() const
{
    return __input;
}

std::string& 
Input::get_value()
{
    return __input;
}

Input& 
Input::operator=(const std::string& rhs)
{
    __input = rhs;
    return *this;
}

Input& 
Input::operator=(const Input& rhs)
{
    __input = rhs.__input;
    return *this;
}

bool 
Input::operator<(const Input& rhs) const
{
    return __input < rhs.__input;
}

bool 
Input::operator==(const Input& rhs)
{
    return __input == rhs.__input;
}

bool 
Input::operator!=(const Input& rhs)
{
    return __input != rhs.__input;
}

} /* namespace PatternMatcher */