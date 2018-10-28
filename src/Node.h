/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 28 October 2018, 7:33 PM
 */

#ifndef PATTERNMATCHER_NODE_H
#define PATTERNMATCHER_NODE_H

#include <map>
#include <memory>
#include <set>

namespace PatternMatcher {

    template <typename PATTERN>
    class Node {
        Node() = delete;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
    public:
        //members
        char value;
        bool is_root;
        Node<PATTERN>* failure;
        std::map<char, std::unique_ptr<Node<PATTERN>>> states;
        std::set<PATTERN> output;
    public:
        //ctors
        virtual ~Node() { }
        Node(char v, bool i = false) 
            : value(v), is_root(i), failure(nullptr) { }

        //member functions
        Node<PATTERN>* g(const char& a) {
            auto result = states.find(a);
            if (states.end() == result) {
                if (is_root) {
                    return this;
                } else {
                    return nullptr;
                }
            }
            else {
                return result->second.get();
            }
        }

        //operators
        bool operator<(const Node<PATTERN>& rhs) const {
            return value < rhs.value;
        } 
    };
    
} /* namespace PatternMatcher */

namespace std {
    template <typename PATTERN>
    struct hash<PatternMatcher::Node<PATTERN>> {
        std::size_t 
        operator()(const PatternMatcher::Node<PATTERN> node) const {
            return std::hash<char>{}(node.value);
        }
    };
}

#endif /* PATTERNMATCHER_NODE_H */

