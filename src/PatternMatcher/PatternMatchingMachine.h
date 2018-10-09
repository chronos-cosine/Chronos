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
#include <set>

#include "IPattern.h"
#include "Node.h"

namespace PatternMatcher
{
 
    class PatternMatchingMachine {
    public:
        typedef boost::signals2::signal<
            void(void* /* sender */, 
                 const unsigned long long& /* total_matches */,
                 PatternMatcher::IPattern* /* input */)> completed_signal;
        typedef boost::signals2::signal<
            void(void* /* sender */, 
                 const unsigned long long& /* position */,
                 PatternMatcher::IPattern* /* input */,
                 const std::set<PatternMatcher::IPattern*>& /* patterns */)> match_found_signal;
    public:
        PatternMatchingMachine(const std::set<IPattern*>& patterns); 
        virtual ~PatternMatchingMachine(); 
 
        void match(IPattern* input, void* sender) const; 

        completed_signal& completed();
        match_found_signal& match_found();

    private:
        void enter(IPattern* pattern);
        void construct_goto_function(const std::set<IPattern*>& patterns);
        void construct_failure_function();
    private:
        Node* __root;
        completed_signal __completed;
        match_found_signal __match_found;
        
    }; /* class PatternMatchingMachine */

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_H */

