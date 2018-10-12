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
#include <set>

#include "IPattern.h"
#include "Node.h"

namespace PatternMatcher
{
    class PatternMatchingMachine {
    public:
        typedef boost::signals2::signal<
            void(const std::shared_ptr<void>& /* sender */, 
                 const unsigned long long& /* total_matches */,
                 const std::shared_ptr<PatternMatcher::IPattern>& /* input */)> completed_signal;
        typedef boost::signals2::signal<
            void(const std::shared_ptr<void>& /* sender */, 
                 const unsigned long long& /* position */,
                 const std::shared_ptr<PatternMatcher::IPattern>& /* input */,
                 const std::set<std::shared_ptr<PatternMatcher::IPattern>>& /* patterns */)> match_found_signal;
    public:
        PatternMatchingMachine(const PatternMatchingMachine&) = delete;
        PatternMatchingMachine& operator=(PatternMatchingMachine&) = delete;
        PatternMatchingMachine(PatternMatchingMachine&& move) = delete;
        PatternMatchingMachine& operator=(PatternMatchingMachine&& move) = delete;
    public:
        PatternMatchingMachine(const std::set<std::shared_ptr<IPattern>>& patterns); 
        virtual ~PatternMatchingMachine(); 
 
        void match(const std::shared_ptr<PatternMatcher::IPattern>& input, 
                   const std::shared_ptr<void>& sender) const; 

        completed_signal& completed();
        match_found_signal& match_found();
        
    private:
        void enter(const std::shared_ptr<PatternMatcher::IPattern>& pattern);
        void construct_goto_function(const std::set<std::shared_ptr<IPattern>>& patterns);
        void construct_failure_function();
    private:
        std::shared_ptr<Node> __root;
        completed_signal __completed;
        match_found_signal __match_found;
        
    }; /* class PatternMatchingMachine */

} /* namespace PatternMatcher */

#endif /* PATTERNMATCHER_PATTERNMATCHINGMACHINE_H */

