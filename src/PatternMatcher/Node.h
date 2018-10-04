/* 
 * File:   Node.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_NODE_H
#define PATTERNMATCHER_NODE_H

#include "IPattern.h"

#include <boost/functional/hash.hpp>
#include <map>
#include <set>

namespace PatternMatcher
{

class Node 
{
public:
    struct Hasher
    {
        std::size_t operator()(const Node& node) const
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
    void add_output(const IPattern& output);
    void add_output(const std::set<IPattern>& outputs);
    std::set<IPattern>& get_output();
    
    //states
    std::map<char, Node*>& get_states();
    void add_state(Node* state);
    
    virtual Node* g(const char& a);
    void clear();
    
    //operators
    bool operator<(const Node& rhs) const;
    bool operator>(const Node& rhs) const;
    
private:
    char __value;
    Node* __failure;
    std::map<char, Node*> __states;
    std::set<IPattern> __output;
};

} /* namespace PatternMatcher */
 
#endif /* PATTERNMATCHER_NODE_H */

