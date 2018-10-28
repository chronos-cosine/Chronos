/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchingMachine.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 28 October 2018, 8:40 PM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_H
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_H

#include "Node.h"

#include <memory>
#include <queue>
#include <set>


namespace PatternMatcher {

    template <typename INPUT = std::string, typename PATTERN = std::string, typename SENDER = void*>
    class PatternMatchingMachine {
    private:
        std::unique_ptr<Node<PATTERN>> root;
    public:
        ~PatternMatchingMachine();
        PatternMatchingMachine(const std::set<PATTERN>& patterns);
    private:
        void enter(const PATTERN& pattern);
        void construct_goto_function(const std::set<PATTERN>& patterns);
        void construct_failure_function();
    };
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::~PatternMatchingMachine() { }
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::PatternMatchingMachine(const std::set<PATTERN>& patterns)
            : root(std::make_unique<Node<PATTERN>>('~', true)) {
        construct_goto_function(patterns);
        construct_failure_function();
    }
   
    template <typename INPUT, typename PATTERN, typename SENDER>
    void  
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::enter(const PATTERN& pattern) { 
        Node<PATTERN>* current = root.get();
        for (const char a: pattern) {
            Node<PATTERN>* new_node = current->g(a);
            if (nullptr == new_node 
                || root.get() == new_node) {
                current->states[a] = std::make_unique<Node<PATTERN>>(a);
            }
            current = current->states[a].get();
        }

        current->output.insert(pattern);
    }
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_goto_function(const std::set<PATTERN>& patterns) { 
        for (const PATTERN& pattern: patterns) {
            enter(pattern);
        }
    }
        
    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_failure_function() {
        std::queue<Node<PATTERN>*> queue;

        for (auto& a: root->states) {
            queue.push(a.second.get());
            a.second->failure = root.get();
        }

        while (!queue.empty()) {
            Node<PATTERN>* r = queue.front();
            queue.pop();

            for (auto& s: r->states) {
                char a = s.first;
                queue.push(s.second.get());
                Node<PATTERN>* state = r->failure;
                while (nullptr == state->g(a)) {
                    state = state->failure; 
                }
                s.second->failure = state->g(a);
                
                for (auto& o: s.second->failure->output) {
                    s.second->output.insert(o);
                }
            }
        }
    }
    
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_H */

