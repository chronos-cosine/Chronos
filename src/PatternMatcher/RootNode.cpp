/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include "RootNode.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename T>
RootNode<T>::RootNode()
    : Node<T>('~')
{
    Node<T>::set_failure(this);
}

template <typename T>
RootNode<T>::~RootNode() 
{
    Node<T>::clear();
}

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

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class RootNode<Pattern>; 

} /* namespace PatternMatcher */
