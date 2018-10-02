/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include <type_traits>

#include "RootNode.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename T>
RootNode<T>::RootNode()
    : Node<T>('~')
{
    static_assert(std::is_base_of<Pattern, T>::value, "<T> must derive from PatternMatcher::Pattern");
    
    // a RootNode fails towards itself
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
