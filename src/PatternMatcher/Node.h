/* 
 * File:   Node.h
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_NODE_H
#define PATTERNMATCHER_NODE_H

#include "IPattern.h"

#include <map>
#include <memory>
#include <set>

namespace PatternMatcher
{
    class Node {
    public:
        struct Hasher {
            std::size_t operator()(const Node& node) const noexcept {
                return std::hash<char>{}(node.__value);
            }
        };
    public:
        Node(Node&) = delete;
        Node& operator=(Node&) = delete;
        bool operator==(Node&) = delete;
        bool operator!=(Node&) = delete;
    public:
        //constructors
        Node(const char& value);
        Node(Node&& move);
        virtual ~Node();

        //member functions
        std::shared_ptr<Node> get_failure(); 
        void set_failure(const std::shared_ptr<Node>& failure); 
        char get_value(); 
        void add_output(const std::shared_ptr<IPattern>& output);
        void add_output(const std::set<std::shared_ptr<IPattern>>& outputs);
        std::set<std::shared_ptr<IPattern>>& get_output(); 
        std::map<char, std::shared_ptr<Node>>& get_states();
        void add_state(const std::shared_ptr<Node>& state); 
        virtual std::shared_ptr<Node> g(const char& a);
        void clear();
        std::map<char, std::shared_ptr<Node>>::iterator begin();
        std::map<char, std::shared_ptr<Node>>::const_iterator begin() const;
        std::map<char, std::shared_ptr<Node>>::iterator end();
        std::map<char, std::shared_ptr<Node>>::const_iterator end() const;

        //operators
        virtual bool operator<(const Node& rhs) const;
        virtual bool operator>(const Node& rhs) const;
        virtual Node& operator=(Node&& move);
    private:
        char __value;
        std::shared_ptr<Node> __failure;
        std::map<char, std::shared_ptr<Node>> __states;
        std::set<std::shared_ptr<IPattern>> __output;
        
    }; /* class Node */
    
} /* namespace PatternMatcher */
 
#endif /* PATTERNMATCHER_NODE_H */

