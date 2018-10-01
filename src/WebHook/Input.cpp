/* 
 * File:   Input.cpp
 * Author: user
 * 
 * Created on 01 October 2018, 7:16 AM
 */

#include "Input.hpp"

namespace WebHook 
{

Input::Input(const unsigned long long& id, 
             const std::string& data)
   : __id(id), __data(data)
{ }

Input::Input(const Input& orig) 
   : __id(orig.get_id()), __data(orig.get_data())
{ }

Input::~Input() 
{ }

const unsigned long long& 
Input::get_id() const
{
    return __id;
}

const std::string& 
Input::get_data() const
{
    return __data;
}
    