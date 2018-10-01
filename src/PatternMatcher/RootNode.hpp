/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_ROOTNODE_HPP
#define PATTERNMATCHER_ROOTNODE_HPP

#include "Node.hpp"

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class RootNode : public Node<PATTERN_TYPE> 
{
public:
    RootNode(); 
    virtual ~RootNode();
    
    virtual Node<PATTERN_TYPE>* g(const char& a); 
};

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_HPP */

