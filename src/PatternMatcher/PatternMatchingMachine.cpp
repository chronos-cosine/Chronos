/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#include "Pattern.hpp"
#include "PatternMatchingMachine.hpp"
#include "RootNode.hpp"

#include <map>
#include <queue>
#include <type_traits>

namespace PatternMatcher
{

template <typename T>
PatternMatchingMachine<T>::PatternMatchingMachine(const std::set<T>& patterns) 
{
    static_assert(std::is_base_of<Pattern, T>::value, "<T> must derive from PatternMatcher::Pattern");
    
    __root = new RootNode<T>();
    construct_goto_function(patterns);
    construct_failure_function();
}

template <typename T>
PatternMatchingMachine<T>::~PatternMatchingMachine() 
{
    __root->clear();
    delete __root;
}

template <typename T>
void 
PatternMatchingMachine<T>::construct_goto_function(const std::set<T>& patterns)
{
    __root->clear();
    for (const T& pattern: patterns)
    {
        enter(pattern);
    }
}

template <typename T>
void 
PatternMatchingMachine<T>::construct_failure_function()
{
    std::queue<Node<T>*> queue;
    for (typename std::map<char, Node<T>*>::iterator a = __root->get_states().begin();
         a != __root->get_states().end();
         ++a)
    {
        queue.push(a->second);
        a->second->set_failure(__root);
    }
    
    while (!queue.empty())
    {
        Node<T>* r = queue.front();
        queue.pop();
        for (typename std::map<char, Node<T>*>::iterator s = r->get_states().begin();
             s != r->get_states().end();
             ++s)
        {
            char a = s->first;
            queue.push(s->second);
            Node<T>* state = r->get_failure();
            while (nullptr == state->g(a)) 
            {
                state = state->get_failure(); 
            }
            s->second->set_failure(state->g(a));
            s->second->add_output(s->second->get_failure()->get_output());
        }
    }
}

template <typename T>
void 
PatternMatchingMachine<T>::enter(const T& pattern)
{
    Node<T>* current = __root;
    for (const char& a: ((Pattern)pattern).get_value())
    {
        Node<T>* new_node = current->g(a);
        if (nullptr == new_node
            || __root == new_node)
        {
            new_node = new Node<T>(a);
            current->add_state(new_node);
        }
        current = new_node;
    }
    current->add_output(pattern);
}

template <typename T>
void 
PatternMatchingMachine<T>::match(const T& input, void* sender) const
{ 
    unsigned long long patterns_found = 0;
    unsigned long long position = 0;
    Node<T>* state = __root;
    
    for (const char& a: ((Pattern)input).get_value())
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

template <typename T>
boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const T&)>& 
PatternMatchingMachine<T>::completed()
{
    return __completed;
}

template <typename T>
boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const T&,
             const std::set<T>&)>& 
PatternMatchingMachine<T>::match_found()
{
    return __match_found;
}

//This section is to ensure that we keep the source code separate in a .cpp for templates
template class PatternMatchingMachine<Pattern>;  

} /* namespace PatternMatcher */
