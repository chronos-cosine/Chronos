/* 
 * File:   Node.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_NODE_HPP
#define PATTERNMATCHER_NODE_HPP

#include <boost/functional/hash.hpp>
#include <map>
#include <set>

namespace PatternMatcher
{

template <typename T>
class Node 
{
public:
    struct Hasher
    {
        std::size_t operator()(const Node<T>& node) const
        {
            boost::hash<char> hash;
            return hash(node.__value);
        }
    };
public:
    //ctor
    Node(const char& value); 
    virtual ~Node();
    
    //failure
    Node* get_failure(); 
    void set_failure(Node* failure);
    
    //value
    char get_value();
    
    //output
    void add_output(const T& output);
    void add_output(const std::set<T>& outputs);
    std::set<T>& get_output();
    
    //states
    std::map<char, Node*>& get_states();
    void add_state(Node* state);
    
    virtual Node* g(const char& a);
    void clear();
    
    //operators
    bool operator<(const Node& rhs) const;
    
private:
    char __value;
    Node* __failure;
    std::map<char, Node*> __states;
    std::set<T> __output;
};


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
    for (auto& tuple: __states)
    {
        tuple.second->clear(); 
        delete tuple.second;
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
    typename std::map<char, Node<T>*>::iterator result = __states.find(state->get_value());
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

} /* namespace PatternMatcher */
 
#endif /* PATTERNMATCHER_NODE_HPP */

