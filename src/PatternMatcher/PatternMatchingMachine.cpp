/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchingMachine.cpp
 * Author: user
 *
 * Created on 05 October 2018, 8:53 AM
 */

#include "PatternMatchingMachine.h"
#include "IPattern.h"
#include "RootNode.h"

#include <queue>

namespace PatternMatcher
{

    PatternMatchingMachine::PatternMatchingMachine(const std::set<IPattern*>& patterns) 
    {
        __root = new RootNode();
        construct_goto_function(patterns);
        construct_failure_function();
    }

    PatternMatchingMachine::~PatternMatchingMachine() 
    {
        __root->clear();
        delete __root;
    }

    void 
    PatternMatchingMachine::construct_goto_function(const std::set<IPattern*>& patterns)
    {
        __root->clear();
        for (IPattern* pattern: patterns)
        {
            enter(pattern);
        }
    }

    void 
    PatternMatchingMachine::construct_failure_function()
    {
        std::queue<Node*> queue;

        for (auto& a: __root->get_states())
        {
            queue.push(a.second);
            a.second->set_failure(__root);
        }

        while (!queue.empty())
        {
            Node* r = queue.front();
            queue.pop();

            for (auto& s: r->get_states())
            {
                char a = s.first;
                queue.push(s.second);
                Node* state = r->get_failure();
                while (nullptr == state->g(a)) 
                {
                    state = state->get_failure(); 
                }
                s.second->set_failure(state->g(a));
                s.second->add_output(s.second->get_failure()->get_output());
            }
        }
    }

    void 
    PatternMatchingMachine::enter(IPattern* pattern)
    {
        Node* current = __root;
        for (const char& a: *pattern)
        {
            Node* new_node = current->g(a);
            if (nullptr == new_node
                || __root == new_node)
            {
                new_node = new Node(a);
                current->add_state(new_node);
            }
            current = new_node;
        }

        current->add_output(pattern);
    }

    void 
    PatternMatchingMachine::match(IPattern* input, void* sender) const
    { 
        unsigned long long patterns_found = 0;
        unsigned long long position = 0;
        Node* state = __root;

        for (const char a: *input)
        { 
            ++position;
            while (nullptr == state->g(a)) 
            {
                state = state->get_failure();
            }
            state = state->g(a);

            if (!state->get_output().empty())
            { 
                __match_found(sender, position, input, state->get_output());
                patterns_found += state->get_output().size();
            } 
        }

        __completed(sender, patterns_found, input); 
    }

    PatternMatchingMachine::completed_signal& 
    PatternMatchingMachine::completed()
    {
        return __completed;
    }

    PatternMatchingMachine::match_found_signal& 
    PatternMatchingMachine::match_found()
    {
        return __match_found;
    }

} /* namespace PatternMatcher */