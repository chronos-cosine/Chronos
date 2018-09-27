/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.hpp
 * Author: user
 *
 * Created on 21 September 2018, 8:10 AM
 */

#ifndef PATTERNMATCHER_NODE_HPP
#define PATTERNMATCHER_NODE_HPP

#include <map>
#include <set>

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class Node {
public:
    //ctor
    Node(const char& value); 
    virtual ~Node();
    
    //failure
    Node* get_failure();
    const Node* get_failure() const;
    void set_failure(Node* failure);
    
    //value
    char get_value();
    const char get_value() const;
    
    //output
    void add_output(const PATTERN_TYPE& output);
    void add_output(const std::set<PATTERN_TYPE>& outputs);
    const std::set<PATTERN_TYPE>& get_output() const;
    std::set<PATTERN_TYPE>& get_output();
    
    //states
    const std::map<char, Node*>& get_states() const;
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
    std::set<PATTERN_TYPE> __output;
};

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_NODE_HPP */

