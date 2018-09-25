/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RootNode.hpp
 * Author: user
 *
 * Created on 21 September 2018, 9:25 AM
 */

#ifndef PATTERNMATCHER_ROOTNODE_HPP
#define PATTERNMATCHER_ROOTNODE_HPP

#include "Node.hpp"

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class RootNode : public Node<PATTERN_TYPE> {
public:
    RootNode(); 
    virtual ~RootNode();
    
    virtual Node<PATTERN_TYPE>* g(const char& a); 
};

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_HPP */

