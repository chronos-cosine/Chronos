/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Node.h"
#include "IPattern.h"

namespace PatternMatcher
{

    Node::Node(const char& value)
        : __value(value), __failure(nullptr) { }

    Node::~Node() {
        clear();
    }

    Node*
    Node::get_failure() {
        return __failure;
    }

    void
    Node::set_failure(Node* failure) {
        __failure = failure;
    }

    char
    Node::get_value() {
        return __value;
    }

    Node*
    Node::g(const char& a) {
        typename std::map<char, Node*>::iterator result = __states.find(a);
        if (__states.end() == result) {
            return nullptr;
        }
        else {
            return result->second;
        }
    }

    void
    Node::add_output(IPattern* output) {
        __output.insert(output);
    }

    void
    Node::add_output(const std::set<IPattern*>& outputs) {
        for (IPattern* output: outputs) {
            add_output(output);
        }
    }

    void
    Node::clear() {
        for (auto& tuple: __states) {
            tuple.second->clear(); 
            delete tuple.second;
        } 
        __states.clear();
    }

    std::set<IPattern*>&
    Node::get_output() {
        return __output;
    }

    std::map<char, Node*>&
    Node::get_states() {
        return __states;
    }

    void
    Node::add_state(Node* state) {
        typename std::map<char, Node*>::iterator result = __states.find(state->get_value());
        if (__states.end() == result) {
            __states[state->get_value()] = state;
        } 
    }
    
    std::map<char, Node*>::iterator 
    Node::begin() noexcept {
        return __states.begin();
    }
    
    std::map<char, Node*>::const_iterator 
    Node::begin() const noexcept {
        return __states.begin();
    }
    
    std::map<char, Node*>::iterator 
    Node::end() noexcept {
        return __states.end();
    }
    
    std::map<char, Node*>::const_iterator 
    Node::end() const noexcept {
        return __states.end();
    }

    bool
    Node::operator<(const Node& rhs) const {
        return __value < rhs.__value;
    }

    bool
    Node::operator>(const Node& rhs) const {
        return __value > rhs.__value;
    }

} /* namespace PatternMatcher */