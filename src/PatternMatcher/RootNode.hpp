/* 
 * File:   RootNode.hpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_ROOTNODE_HPP
#define PATTERNMATCHER_ROOTNODE_HPP

#include "Node.hpp"

namespace PatternMatcher
{

template <typename T>
class RootNode : public Node<T> 
{
public:
    RootNode(); 
    virtual ~RootNode();
    
    virtual Node<T>* g(const char& a); 
};

template <typename T>
RootNode<T>::RootNode()
    : Node<T>('~')
{
    Node<T>::set_failure(this);
}

template <typename T>
RootNode<T>::~RootNode() 
{ }

template <typename T>
Node<T>* 
RootNode<T>::g(const char& a)
{
    Node<T>* state = Node<T>::g(a);
    if (nullptr == state)
    {
        return this;
    }
    else 
    {
        return state;
    }
}

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_ROOTNODE_HPP */

