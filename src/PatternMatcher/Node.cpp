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
    
    Node::Node(Node&& move)
        : __value(std::move(move.__value)), __failure(std::move(move.__failure)),
          __states(std::move(move.__states)), __output(std::move(move.__output)) { }

    Node::~Node() {
        clear();
    }

    std::shared_ptr<Node>
    Node::get_failure() {
        return __failure;
    }

    void
    Node::set_failure(const std::shared_ptr<Node>& failure) {
        __failure = failure;
    }

    char
    Node::get_value() {
        return __value;
    }

    std::shared_ptr<Node>
    Node::g(const char& a) {
        auto result = __states.find(a);
        if (__states.end() == result) {
            return nullptr;
        }
        else {
            return result->second;
        }
    }

    void
    Node::add_output(const std::shared_ptr<IPattern>& output) {
        __output.insert(output);
    }

    void
    Node::add_output(const std::set<std::shared_ptr<IPattern>>& outputs) {
        for (const auto& output: outputs) {
            add_output(output);
        }
    }

    void
    Node::clear() {
        for (auto& tuple: __states) {
            tuple.second->clear();
        } 
        __states.clear();
    }

    std::set<std::shared_ptr<IPattern>>&
    Node::get_output() {
        return __output;
    }

    std::map<char, std::shared_ptr<Node>>&
    Node::get_states() {
        return __states;
    }

    void
    Node::add_state(const std::shared_ptr<Node>& state) {
        auto result = __states.find(state->get_value());
        if (__states.end() == result) {
            __states[state->get_value()] = state;
        } 
    }
    
    std::map<char, std::shared_ptr<Node>>::iterator 
    Node::begin() {
        return __states.begin();
    }
    
    std::map<char, std::shared_ptr<Node>>::const_iterator 
    Node::begin() const {
        return __states.begin();
    }
    
    std::map<char, std::shared_ptr<Node>>::iterator 
    Node::end() {
        return __states.end();
    }
    
    std::map<char, std::shared_ptr<Node>>::const_iterator 
    Node::end() const {
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

    Node& 
    Node::operator=(Node&& move) {
        __value = std::move(move.__value); 
        __failure = std::move(move.__failure);
        __states = std::move(move.__states);
        __output = std::move(move.__output);
        
        return *this;
    }
    
} /* namespace PatternMatcher */