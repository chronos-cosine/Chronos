/* 
 * File:   Bin.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include "Bin.hpp"

namespace Sorter 
{

Bin::~Bin() { }

Bin::Bin(const std::string& name, 
         const unsigned long long& id)
    : __name(name), __id(id)
{
    __parent = nullptr;
}

Bin::Bin(const std::string& name, 
         const unsigned long long& id, 
         Bin* parent)
    : __name(name), __id(id)
{
    __parent = parent;
}


const Bin* 
Bin::get_parent() const
{
    return __parent;
}

Bin* 
Bin::get_parent()
{
    return __parent;
}

const std::string& 
Bin::get_name() const
{
    return __name;
}

const unsigned long long& 
Bin::get_id() const
{
    return __id;
}

unsigned long long 
Bin::get_id()
{
    return __id;
}

} /* namespace Sorter */

