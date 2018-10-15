/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchingMachine.h
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_H
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_H

#include <boost/signals2.hpp>
#include <memory>
#include <queue>
#include <set>
#include <iostream>
 
#include "PatternMatcher/Node.h"
#include "PatternMatcher/RootNode.h"
#include "Core/Exception.h"

namespace PatternMatcher
{
    template <typename INPUT = std::string, typename PATTERN = std::string, typename SENDER = void>
    class PatternMatchingMachine {
    public:
        typedef boost::signals2::signal<
            void(const std::shared_ptr<SENDER>& /* sender */, 
                 const unsigned long long& /* total_matches */,
                 const INPUT& /* input */)> completed_signal;
        typedef boost::signals2::signal<
            void(const std::shared_ptr<SENDER>& /* sender */, 
                 const unsigned long long& /* position */,
                 const INPUT& /* input */,
                 const std::set<std::shared_ptr<PATTERN>>& /* patterns */)> match_found_signal;
    public:
        PatternMatchingMachine(const PatternMatchingMachine&) = delete;
        PatternMatchingMachine& operator=(PatternMatchingMachine&) = delete;
        PatternMatchingMachine(PatternMatchingMachine&& move) = delete;
        PatternMatchingMachine& operator=(PatternMatchingMachine&& move) = delete;
    public:
        PatternMatchingMachine(const std::set<std::shared_ptr<PATTERN>>& patterns); 
        virtual ~PatternMatchingMachine(); 
 
        void match(const INPUT& input, 
                   const std::shared_ptr<SENDER>& sender) const; 

        completed_signal& completed();
        match_found_signal& match_found();
        
    private:
        void enter(const std::shared_ptr<PATTERN>& pattern);
        void construct_goto_function(const std::set<std::shared_ptr<PATTERN>>& patterns);
        void construct_failure_function();
    private:
        Node<PATTERN>* __root;
        completed_signal __completed;
        match_found_signal __match_found;
        
    }; /* class PatternMatchingMachine */
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::PatternMatchingMachine(const std::set<std::shared_ptr<PATTERN>>& patterns) 
        : __root(new RootNode<PATTERN>()) {
        construct_goto_function(patterns);
        construct_failure_function();
    }
        
    template <typename INPUT, typename PATTERN, typename SENDER>
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::~PatternMatchingMachine() {
        __root->clear();
        delete __root;
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_goto_function(const std::set<std::shared_ptr<PATTERN>>& patterns) {
        __root->clear();
        for (const auto& pattern: patterns) {
            enter(pattern);
        }
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_failure_function() {
        std::queue<Node<PATTERN>*> queue;

        for (auto& a: __root->get_states()) {
            queue.push(a.second);
            a.second->set_failure(__root);
        }

        while (!queue.empty()) {
            Node<PATTERN>* r = queue.front();
            queue.pop();

            for (auto& s: r->get_states()) {
                char a = s.first;
                queue.push(s.second);
                Node<PATTERN>* state = r->get_failure();
                while (nullptr == state->g(a)) {
                    state = state->get_failure(); 
                }
                s.second->set_failure(state->g(a));
                s.second->add_output(s.second->get_failure()->get_output());
            }
        }
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::enter(const std::shared_ptr<PATTERN>& pattern) {
        Node<PATTERN>* current = __root;
        for (const char& a: *pattern) {
            Node<PATTERN>* new_node = current->g(a);
            if (nullptr == new_node
                || __root == new_node) {
                new_node = new Node<PATTERN>(a);
                current->add_state(new_node);
            }
            current = new_node;
        }

        current->add_output(pattern);
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::match(const INPUT& input, 
                                  const std::shared_ptr<SENDER>& sender) const { 
        unsigned long long patterns_found = 0;
        unsigned long long position = 0;
        std::shared_ptr<Node<PATTERN>> state = __root;

        for (const char a: input) { 
            ++position;
            while (nullptr == state->g(a)) {
                state = state->get_failure();
            }
            state = state->g(a);

            if (!state->get_output().empty()) { 
                __match_found(sender, position, input, state->get_output());
                patterns_found += state->get_output().size();
            } 
        }

        __completed(sender, patterns_found, input); 
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    typename PatternMatchingMachine<INPUT, PATTERN, SENDER>::completed_signal& 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::completed() {
        return __completed;
    }

    template <typename INPUT, typename PATTERN, typename SENDER>
    typename PatternMatchingMachine<INPUT, PATTERN, SENDER>::match_found_signal& 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::match_found() {
        return __match_found;
    }

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_H */

