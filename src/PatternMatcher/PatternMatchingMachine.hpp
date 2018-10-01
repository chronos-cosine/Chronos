/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP

#include <boost/signals2.hpp>
#include <string>
#include <set>

#include "Node.hpp" 

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class PatternMatchingMachine { 
public:
    PatternMatchingMachine(const std::set<PATTERN_TYPE>& patterns); 
    virtual ~PatternMatchingMachine(); 
    
    void match(const std::string& input, void* sender);
    void match(const char* input, void* sender);
    
    boost::signals2::signal<
        void(void* /* sender */, 
             const unsigned long long& /* total_matches */,
             const std::string& /* input */)>& completed();
    boost::signals2::signal<
        void(void* /* sender */, 
             const unsigned long long& /* position */,
             const std::string& /* input */,
             const std::set<PATTERN_TYPE>& /* patterns */)>& match_found();
private:
    Node<PATTERN_TYPE>* __root;
    boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const std::string&)> __completed;
    boost::signals2::signal<
        void(void*, 
             const unsigned long long&,
             const std::string&,
             const std::set<PATTERN_TYPE>&)> __match_found;
     
    void enter(const PATTERN_TYPE& pattern);
    void construct_goto_function(const std::set<PATTERN_TYPE>& patterns);
    void construct_failure_function();
};
 
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP */

