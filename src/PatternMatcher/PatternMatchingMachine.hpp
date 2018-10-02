/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP

#include <boost/signals2.hpp> 
#include <set>

#include "Node.hpp" 

namespace PatternMatcher
{

template <typename T>
class PatternMatchingMachine { 
public:
    PatternMatchingMachine(const std::set<T>& patterns); 
    virtual ~PatternMatchingMachine(); 
    
    void match(const T& input, void* sender) const; 
    
    boost::signals2::signal<
        void(void* /* sender */, 
             const unsigned long long& /* total_matches */,
             const T& /* input */)>& completed();
    boost::signals2::signal<
        void(void* /* sender */, 
             const unsigned long long& /* position */,
             const T& /* input */,
             const std::set<T>& /* patterns */)>& match_found();
private:
    Node<T>* __root;
    boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const T&)> __completed;
    boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const T&,
             const std::set<T>&)> __match_found;
     
    void enter(const T& pattern);
    void construct_goto_function(const std::set<T>& patterns);
    void construct_failure_function();
};
 
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP */

