/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchingMachine.cpp
 * Author: user
 * 
 * Created on 21 September 2018, 9:40 AM
 */

#include "Pattern.hpp"
#include "PatternMatchingMachine.hpp"
#include "RootNode.hpp"

#include <map>
#include <queue>
#include <type_traits>

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
PatternMatchingMachine<PATTERN_TYPE>::PatternMatchingMachine(const std::set<PATTERN_TYPE>& patterns) 
{
    static_assert(std::is_base_of<Pattern, PATTERN_TYPE>::value, "<PATTERN_TYPE> must derive from PatternMatcher::Pattern");
    
    __root = new RootNode<PATTERN_TYPE>();
    construct_goto_function(patterns);
    construct_failure_function();
}

template <typename PATTERN_TYPE>
PatternMatchingMachine<PATTERN_TYPE>::~PatternMatchingMachine() 
{
    __root->clear();
    delete __root;
}

template <typename PATTERN_TYPE>
void 
PatternMatchingMachine<PATTERN_TYPE>::construct_goto_function(const std::set<PATTERN_TYPE>& patterns)
{
    __root->clear();
    for (const PATTERN_TYPE& pattern: patterns)
    {
        enter(pattern);
    }
}

template <typename PATTERN_TYPE>
void 
PatternMatchingMachine<PATTERN_TYPE>::construct_failure_function()
{
    std::queue<Node<PATTERN_TYPE>*> queue;
    for (typename std::map<char, Node<PATTERN_TYPE>*>::iterator a = __root->get_states().begin();
         a != __root->get_states().end();
         ++a)
    {
        queue.push(a->second);
        a->second->set_failure(__root);
    }
    
    while (!queue.empty())
    {
        Node<PATTERN_TYPE>* r = queue.front();
        queue.pop();
        for (typename std::map<char, Node<PATTERN_TYPE>*>::iterator s = r->get_states().begin();
             s != r->get_states().end();
             ++s)
        { 
            char a = s->first;
            queue.push(s->second);
            Node<PATTERN_TYPE>* state = r->get_failure();
            while (nullptr == state->g(a)) 
            {
                state = state->get_failure(); 
            }
            s->second->set_failure(state->g(a));
            s->second->add_output(s->second->get_failure()->get_output());
        }
    }
}

template <typename PATTERN_TYPE>
void 
PatternMatchingMachine<PATTERN_TYPE>::enter(const PATTERN_TYPE& pattern)
{
    Node<PATTERN_TYPE>* current = __root;
    for (const char& a: pattern.get_value())
    {
        Node<PATTERN_TYPE>* new_node = current->g(a);
        if (nullptr == new_node
            || __root == new_node)
        {
            new_node = new Node<PATTERN_TYPE>(a);
            current->add_state(new_node);
        }
        current = new_node;
    }
    current->add_output(pattern);
}

template <typename PATTERN_TYPE>
void 
PatternMatchingMachine<PATTERN_TYPE>::match(const char* input)
{
    std::string temp(input);
    match(temp);
}

template <typename PATTERN_TYPE>
void 
PatternMatchingMachine<PATTERN_TYPE>::match(const std::string& input)
{ 
    unsigned long long patterns_found = 0;
    unsigned long long position = 0;
    Node<PATTERN_TYPE>* state = __root;
    
    for (const char& a: input)
    {
        ++position;
        while (nullptr == state->g(a)) 
        {
            state = state->get_failure();
        }
        state = state->g(a);
        
        if (!state->get_output().empty())
        { 
            __match_found(this, position, input, state->get_output());
            patterns_found += state->get_output().size();
        } 
    }
     
    __completed(this, patterns_found, input); 
}

template <typename PATTERN_TYPE>
boost::signals2::signal<
        void(PatternMatchingMachine<PATTERN_TYPE>*, 
             const unsigned long long&,
             const std::string&)>& 
PatternMatchingMachine<PATTERN_TYPE>::completed()
{
    return __completed;
}

template <typename PATTERN_TYPE>
boost::signals2::signal<
        void(PatternMatchingMachine<PATTERN_TYPE>*, 
             const unsigned long long&,
             const std::string&,
             const std::set<PATTERN_TYPE>&)>& 
PatternMatchingMachine<PATTERN_TYPE>::match_found()
{
    return __match_found;
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class PatternMatchingMachine<Pattern>; 

} /* namespace PatternMatcher */
