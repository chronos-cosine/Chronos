/* 
 * File:   Bin.hpp
 * Author: user
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

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_NODE_HPP */

