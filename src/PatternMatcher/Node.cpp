/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */
 
#include <map>
#include <set>

#include "Node.hpp"
#include "Pattern.hpp"

namespace PatternMatcher
{

template <typename T>
Node<T>::Node(const char& value)
    : __value(value), __failure(nullptr)
{ }
 
template <typename T>
Node<T>::~Node()
{
    clear();
}

template <typename T>
Node<T>*
Node<T>::get_failure()
{
    return __failure;
}

template <typename T>
void
Node<T>::set_failure(Node<T>* failure)
{
    __failure = failure;
}

template <typename T>
char
Node<T>::get_value()
{
    return __value;
}

template <typename T>
Node<T>*
Node<T>::g(const char& a)
{
    typename std::map<char, Node<T>*>::iterator result = __states.find(a);
    if (__states.end() == result)
    {
        return nullptr;
    }
    else 
    {
        return result->second;
    }
}

template <typename T>
void
Node<T>::add_output(const T& output)
{
    __output.insert(output);
}

template <typename T>
void
Node<T>::add_output(const std::set<T>& outputs)
{
    for (const T& output: outputs)
    {
        add_output(output);
    }
}

template <typename T>
void
Node<T>::clear()
{
    for (typename std::map<char, Node<T>*>::iterator iter = __states.begin();
         iter != __states.end();
         ++iter)
    {
        iter->second->clear(); 
        delete iter->second;
    }
    
    __states.clear();
}

template <typename T>
std::set<T>&
Node<T>::get_output()
{
    return __output;
}

template <typename T>
std::map<char, Node<T>*>&
Node<T>::get_states()
{
    return __states;
}

template <typename T>
void
Node<T>::add_state(Node<T>* state)
{
    typename std::map<char, Node<T>*>::const_iterator result = __states.find(state->get_value());
    if (__states.end() == result)
    {
        __states[state->get_value()] = state;
    } 
}

template <typename T>
bool
Node<T>::operator<(const Node<T>& rhs) const
{
    return __value < rhs.__value;
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class Node<Pattern>;
 
} /* namespace PatternMatcher */
