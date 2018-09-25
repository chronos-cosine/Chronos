/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PatternMatchingMachine.hpp
 * Author: user
 *
 * Created on 21 September 2018, 9:40 AM
 */

#ifndef PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP
#define PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP

#include "Node.hpp"
#include "CompletedSignalArgs.hpp"
#include "MatchFoundSignalArgs.hpp"

#include <boost/signals2.hpp>
#include <string>
#include <set>

namespace PatternMatcher
{

template <typename PATTERN_TYPE>
class PatternMatchingMachine {
public:
    typedef boost::signals2::signal<void(PatternMatchingMachine<PATTERN_TYPE>*, const CompletedSignalArgs&)> signal_completed;
    typedef boost::signals2::signal<void(PatternMatchingMachine<PATTERN_TYPE>*, const MatchFoundSignalArgs<PATTERN_TYPE>&)> signal_match_found;
public:
    PatternMatchingMachine(const std::set<PATTERN_TYPE>& patterns); 
    virtual ~PatternMatchingMachine(); 
    
    void match(const std::string& input);
    
    signal_completed& completed();
    signal_match_found& match_found();
private:
    Node<PATTERN_TYPE>* __root;
    signal_completed __completed;
    signal_match_found __match_found;
     
    void enter(const PATTERN_TYPE& pattern);
    void construct_goto_function(const std::set<PATTERN_TYPE>& patterns);
    void construct_failure_function();
};
 
} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_HPP */

