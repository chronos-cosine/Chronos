/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatcher/Node.h
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
    class Node : public std::enable_shared_from_this<Node<PATTERN>> {
        Node() = delete;
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
    public:
        //members
        char value;
        bool is_root;
        std::shared_ptr<Node<PATTERN>> failure;
        std::map<char, std::shared_ptr<Node<PATTERN>>> states;
        std::set<std::shared_ptr<PATTERN>> output;
    public:
        virtual ~Node() = default;
        Node(char v, bool i = false);

        std::shared_ptr<Node<PATTERN>> g(const char& a);
        bool operator<(const Node<PATTERN>& rhs) const;
    };
    
    template <typename PATTERN>
    Node<PATTERN>::Node(char v, bool i) 
            : value(v), is_root(i), failure(nullptr) { }

    template <typename PATTERN>
    std::shared_ptr<Node<PATTERN>> 
    Node<PATTERN>::g(const char& a) {
        auto result = states.find(a);
        if (states.end() == result) {
            if (is_root) {
                return std::enable_shared_from_this<Node<PATTERN>>::shared_from_this();
            } else {
                return std::shared_ptr<Node<PATTERN>>(nullptr);
            }
        }
        else {
            return result->second;
        }
    }

    template <typename PATTERN>
    bool 
    Node<PATTERN>::operator<(const Node<PATTERN>& rhs) const {
        return value < rhs.value;
    } 
    
} /* namespace PatternMatcher */

namespace std {
    
    template <typename PATTERN>
    struct hash<PatternMatcher::Node<PATTERN>> {
        
        std::size_t 
        operator()(const PatternMatcher::Node<PATTERN> node) const {
            return std::hash<char>{}(node.value);
        }
        
    }; /* struct hash<PatternMatcher::Node<PATTERN>> */ 
} /* namespace std */

#endif /* PATTERNMATCHER_NODE_H */

