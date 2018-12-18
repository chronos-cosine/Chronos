/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatcher/PatternMatchingMachine.h
 * Author: Chronos Cosine <chronos.cosine@gmail.com>
 *
 * Created on 28 October 2018, 8:40 PM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_H
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_H

#include "PatternMatcher/Node.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace PatternMatcher {

    template <typename INPUT = std::string, 
              typename PATTERN = std::string, 
              typename SENDER = void>
    class PatternMatchingMachine {
    public:
        virtual ~PatternMatchingMachine() = default;
        PatternMatchingMachine(const std::vector<std::shared_ptr<PATTERN>>& t_patterns);
    public:
        void match(const std::shared_ptr<INPUT>& input, SENDER* t_sender) const;
    private:
        void enter(const std::shared_ptr<PATTERN>& t_pattern);
        void construct_goto_function(const std::vector<std::shared_ptr<PATTERN>>& t_patterns);
        void construct_failure_function();
    public:
        std::function<void(SENDER*          /* t_sender */, 
            const std::shared_ptr<INPUT>&   /* t_input */,
            const uint64_t &                /* t_total_matches */)> completed;
        std::function<void(SENDER*                      /* t_sender */, 
            const std::shared_ptr<INPUT>&               /* t_input */,
            const uint64_t&                             /* t_position */,
            const std::set<std::shared_ptr<PATTERN>>&   /* t_patterns */)> match_found;
    private:
        std::shared_ptr<Node<PATTERN>> m_root;
    };
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::PatternMatchingMachine(
                        const std::vector<std::shared_ptr<PATTERN>>& t_patterns)
      : m_root(std::make_unique<Node<PATTERN>>('~', true)),
        completed(nullptr), 
        match_found(nullptr) {
        construct_goto_function(t_patterns);
        construct_failure_function();
    }
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::match(
                                            const std::shared_ptr<INPUT>& t_input,
                                            SENDER* t_sender) const { 
        uint64_t patterns_found = 0;
        uint64_t position = 0;
        std::shared_ptr<Node<PATTERN>> state = m_root;

        for (const char a: *t_input) { 
            ++position;
            while (nullptr == state->g(a)) {
                state = state->failure;
            }
            state = state->g(a);

            if (!state->output.empty()) {
                if (nullptr != match_found)
                {
                    match_found(t_sender, t_input, position, state->output);
                }
                patterns_found += state->output.size();
            } 
        }

        if (nullptr != completed) {
           completed(t_sender, t_input, patterns_found); 
        }
    }
   
    template <typename INPUT, typename PATTERN, typename SENDER>
    void  
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::enter(const std::shared_ptr<PATTERN>& t_pattern) { 
        std::shared_ptr<Node<PATTERN>> current = m_root;
        for (const char a: *t_pattern) {
            std::shared_ptr<Node<PATTERN>> new_node = current->g(a);
            if (nullptr == new_node 
                || m_root == new_node) {
                current->states[a] = std::make_shared<Node<PATTERN>>(a);
            }
            current = current->states[a];
        }

        current->output.insert(t_pattern);
    }
    
    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_goto_function(
                        const std::vector<std::shared_ptr<PATTERN>>& t_patterns) { 
        for (auto pattern: t_patterns) {
            enter(pattern);
        }
    }
        
    template <typename INPUT, typename PATTERN, typename SENDER>
    void 
    PatternMatchingMachine<INPUT, PATTERN, SENDER>::construct_failure_function() {
        std::queue<std::shared_ptr<Node<PATTERN>>> queue;

        for (auto& a: m_root->states) {
            queue.push(a.second);
            a.second->failure = m_root;
        }

        while (!queue.empty()) {
            std::shared_ptr<Node<PATTERN>> r = queue.front();
            queue.pop();

            for (auto& s: r->states) {
                char a = s.first;
                queue.push(s.second);
                std::shared_ptr<Node<PATTERN>> state = r->failure;
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

