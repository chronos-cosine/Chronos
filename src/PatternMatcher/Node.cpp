/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 8:10 AM
 */
 
#include <map>
#include <set>

#include "Node.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
Node<PATTERN_TYPE>::Node(const char& value)
    : __value(value)
{ 
    __failure = nullptr;
}
 
template <typename PATTERN_TYPE>
Node<PATTERN_TYPE>::~Node() 
{
    clear();
}

template <typename PATTERN_TYPE>
Node<PATTERN_TYPE>* 
Node<PATTERN_TYPE>::get_failure()
{
    return __failure;
}

template <typename PATTERN_TYPE>
const Node<PATTERN_TYPE>* 
Node<PATTERN_TYPE>::get_failure() const
{
    return __failure;
}

template <typename PATTERN_TYPE>
void 
Node<PATTERN_TYPE>::set_failure(Node<PATTERN_TYPE>* failure)
{
    __failure = failure;
}
 
template <typename PATTERN_TYPE>
char 
Node<PATTERN_TYPE>::get_value()
{
    return __value;
}

template <typename PATTERN_TYPE>
const char 
Node<PATTERN_TYPE>::get_value() const
{
    return __value;
}

template <typename PATTERN_TYPE>
Node<PATTERN_TYPE>* 
Node<PATTERN_TYPE>::g(const char& a)
{
    typename std::map<char, Node<PATTERN_TYPE>*>::iterator result = __states.find(a);
    if (__states.end() == result)
    {
        return nullptr;
    }
    else 
    {
        return result->second;
    }
}

template <typename PATTERN_TYPE>
void 
Node<PATTERN_TYPE>::add_output(const PATTERN_TYPE& output)
{
    __output.insert(output);
}

template <typename PATTERN_TYPE>
void 
Node<PATTERN_TYPE>::add_output(const std::set<PATTERN_TYPE>& outputs)
{
    for (const PATTERN_TYPE& output: outputs)
    {
        add_output(output);
    }
}

template <typename PATTERN_TYPE>
void 
Node<PATTERN_TYPE>::clear()
{
    /*
     * This section is very important because 
     * the PatternMatchingMachine is dynamically 
     * creating Nodes.
     */
    for (typename std::map<char, Node<PATTERN_TYPE>*>::iterator iter = __states.begin();
         iter != __states.end();
         ++iter)
    {
        iter->second->clear();
        delete iter->second;
    }
    
    __states.clear();
}

template <typename PATTERN_TYPE>
const std::set<PATTERN_TYPE>& 
Node<PATTERN_TYPE>::get_output() const
{
    return __output;
}

template <typename PATTERN_TYPE>
std::set<PATTERN_TYPE>& 
Node<PATTERN_TYPE>::get_output()
{
    return __output;
}


template <typename PATTERN_TYPE>
const std::map<char, Node<PATTERN_TYPE>*>& 
Node<PATTERN_TYPE>::get_states() const
{
    return __states;
}

template <typename PATTERN_TYPE>
std::map<char, Node<PATTERN_TYPE>*>& 
Node<PATTERN_TYPE>::get_states()
{
    return __states;
}

template <typename PATTERN_TYPE>
void 
Node<PATTERN_TYPE>::add_state(Node<PATTERN_TYPE>* state)
{
    typename std::map<char, Node<PATTERN_TYPE>*>::const_iterator result = __states.find(state->get_value());
    if (__states.end() == result)
    {
        __states[state->get_value()] = state;
    } 
}

template <typename PATTERN_TYPE>
bool 
Node<PATTERN_TYPE>::operator<(const Node<PATTERN_TYPE>& rhs) const
{
    return __value < rhs.__value;
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class Node<Pattern>; 
 
} /* namespace PatternMatcher */
