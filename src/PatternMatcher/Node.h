/* 
 * File:   Node.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_NODE_H
#define PATTERNMATCHER_NODE_H

#include <map>
#include <memory>
#include <set>

namespace PatternMatcher
{
    template <typename PATTERN>
    class Node {
    public:
        struct Hasher {
            std::size_t operator()(const Node<PATTERN>& node) const noexcept {
                return std::hash<char>{}(node.__value);
            }
        };
    public:
        Node(Node<PATTERN>&) = delete;
        Node<PATTERN>& operator=(Node<PATTERN>&) = delete;
        bool operator==(Node<PATTERN>&) = delete;
        bool operator!=(Node<PATTERN>&) = delete;
    public:
        //constructors
        Node(const char& value);
        virtual ~Node();

        //member functions
        virtual std::shared_ptr<Node<PATTERN>> g(const char& a);
        
        std::shared_ptr<Node<PATTERN>> get_failure(); 
        void set_failure(const std::shared_ptr<Node<PATTERN>>& failure); 
        char get_value(); 
        void add_output(const std::shared_ptr<PATTERN>& output);
        void add_output(const std::set<std::shared_ptr<PATTERN>>& outputs);
        std::set<std::shared_ptr<PATTERN>>& get_output(); 
        std::map<char, std::shared_ptr<Node<PATTERN>>>& get_states();
        void add_state(const std::shared_ptr<Node<PATTERN>>& state); 
        void clear();
        typename std::map<char, std::shared_ptr<Node<PATTERN>>>::iterator begin();
        typename std::map<char, std::shared_ptr<Node<PATTERN>>>::const_iterator begin() const;
        typename std::map<char, std::shared_ptr<Node<PATTERN>>>::iterator end();
        typename std::map<char, std::shared_ptr<Node<PATTERN>>>::const_iterator end() const;

        //operators
        bool operator<(const Node<PATTERN>& rhs) const;
        bool operator>(const Node<PATTERN>& rhs) const;
    private:
        char __value;
        std::shared_ptr<Node<PATTERN>> __failure;
        std::map<char, std::shared_ptr<Node<PATTERN>>> __states;
        std::set<std::shared_ptr<PATTERN>> __output;
        
    }; /* class Node */
    
    template <typename PATTERN>
    Node<PATTERN>::Node(const char& value)
        : __value(value), __failure(nullptr) { }
    
    template <typename PATTERN>
    Node<PATTERN>::~Node() {
        clear();
    }

    template <typename PATTERN>
    std::shared_ptr<Node<PATTERN>>
    Node<PATTERN>::get_failure() {
        return __failure;
    }

    template <typename PATTERN>
    void
    Node<PATTERN>::set_failure(const std::shared_ptr<Node>& failure) {
        __failure = failure;
    }

    template <typename PATTERN>
    char
    Node<PATTERN>::get_value() {
        return __value;
    }

    template <typename PATTERN>
    std::shared_ptr<Node<PATTERN>>
    Node<PATTERN>::g(const char& a) {
        auto result = __states.find(a);
        if (__states.end() == result) {
            return nullptr;
        }
        else {
            return result->second;
        }
    }

    template <typename PATTERN>
    void
    Node<PATTERN>::add_output(const std::shared_ptr<PATTERN>& output) {
        __output.insert(output);
    }

    template <typename PATTERN>
    void
    Node<PATTERN>::add_output(const std::set<std::shared_ptr<PATTERN>>& outputs) {
        for (const auto& output: outputs) {
            add_output(output);
        }
    }

    template <typename PATTERN>
    void
    Node<PATTERN>::clear() {
        for (auto& tuple: __states) {
            tuple.second->clear();
        } 
        __states.clear();
    }

    template <typename PATTERN>
    typename std::set<std::shared_ptr<PATTERN>>&
    Node<PATTERN>::get_output() {
        return __output;
    }

    template <typename PATTERN>
    typename std::map<char, std::shared_ptr<Node<PATTERN>>>&
    Node<PATTERN>::get_states() {
        return __states;
    }

    template <typename PATTERN>
    void
    Node<PATTERN>::add_state(const std::shared_ptr<Node<PATTERN>>& state) {
        auto result = __states.find(state->get_value());
        if (__states.end() == result) {
            __states[state->get_value()] = state;
        } 
    }
    
    template <typename PATTERN>
    typename std::map<char, std::shared_ptr<Node<PATTERN>>>::iterator 
    Node<PATTERN>::begin() {
        return __states.begin();
    }
    
    template <typename PATTERN>
    typename std::map<char, std::shared_ptr<Node<PATTERN>>>::const_iterator 
    Node<PATTERN>::begin() const {
        return __states.begin();
    }
    
    template <typename PATTERN>
    typename std::map<char, std::shared_ptr<Node<PATTERN>>>::iterator 
    Node<PATTERN>::end() {
        return __states.end();
    }
    
    template <typename PATTERN>
    typename std::map<char, std::shared_ptr<Node<PATTERN>>>::const_iterator 
    Node<PATTERN>::end() const {
        return __states.end();
    }

    template <typename PATTERN>
    bool
    Node<PATTERN>::operator<(const Node<PATTERN>& rhs) const {
        return __value < rhs.__value;
    }

    template <typename PATTERN>
    bool
    Node<PATTERN>::operator>(const Node<PATTERN>& rhs) const {
        return __value > rhs.__value;
    }

} /* namespace PatternMatcher */
 
#endif /* PATTERNMATCHER_NODE_H */

