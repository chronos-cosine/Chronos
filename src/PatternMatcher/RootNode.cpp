/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RootNode.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 9:25 AM
 */

#include <type_traits>

#include "RootNode.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
RootNode<PATTERN_TYPE>::RootNode()
    : Node<PATTERN_TYPE>('~')
{
    static_assert(std::is_base_of<Pattern, PATTERN_TYPE>::value, "<PATTERN_TYPE> must derive from PatternMatcher::Pattern");
    
    // a RootNode fails towards itself
    Node<PATTERN_TYPE>::set_failure(this);
}

template <typename PATTERN_TYPE>
RootNode<PATTERN_TYPE>::~RootNode() 
{
    Node<PATTERN_TYPE>::clear();
}

template <typename PATTERN_TYPE>
Node<PATTERN_TYPE>* 
RootNode<PATTERN_TYPE>::g(const char& a)
{
    Node<PATTERN_TYPE>* state = Node<PATTERN_TYPE>::g(a);
    if (nullptr == state)
    {
        return this;
    }
    else 
    {
        return state;
    }
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class RootNode<Pattern>; 

} /* namespace PatternMatcher */
