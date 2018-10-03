/* 
 * File:   PatternMatchingMachineTests.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_PATTERNMATCHINGMACHINE_TESTS_CPP
#define TESTS_PATTERNMATCHER_PATTERNMATCHINGMACHINE_TESTS_CPP
 
#include <gtest/gtest.h> 
#include <iostream>
#include <set>
#include "../../src/PatternMatcher/RootNode.hpp" 
#include "../../src/PatternMatcher/Node.hpp" 
#include "../../src/PatternMatcher/Pattern.hpp" 
#include "../../src/PatternMatcher/PatternMatchingMachine.hpp" 

static PatternMatcher::Pattern __completed_input("");
static void* __completed_sender; 
static std::set<PatternMatcher::Pattern> __patterns;
static std::set<unsigned long long> __positions;
static unsigned long long __total_matches;

struct completed
{
    void operator()(void* sender , 
             const unsigned long long& total_matches,
             const PatternMatcher::Pattern& input )
    {
        __total_matches = total_matches;
        __completed_sender = sender;
        __completed_input = input;
    }
};

struct matchfound 
{
    void operator()(void* sender , 
             const unsigned long long& position,
             const PatternMatcher::Pattern& input ,
             const std::set<PatternMatcher::Pattern>& patterns)
    {
        __positions.insert(position);
        for (auto& p: patterns)
        {
            __patterns.insert(p);
        }
    }
};


TEST(PatternMatcherTests, test_patternmatchingmachine_match) {
    completed completed;
    matchfound matchfound;
    int* sender = new int(123);
    std::set<PatternMatcher::Pattern> patterns = { PatternMatcher::Pattern("he"), 
                                                   PatternMatcher::Pattern("she"),  
                                                   PatternMatcher::Pattern("his"),  
                                                   PatternMatcher::Pattern("hers") };
   PatternMatcher::Pattern input("This is a test for her");
   PatternMatcher::PatternMatchingMachine<PatternMatcher::Pattern> pmm(patterns);
   pmm.completed().connect(completed);
   pmm.match_found().connect(matchfound);
   pmm.match(input, sender);
   
   ASSERT_EQ(__completed_input, input);
   ASSERT_EQ(__completed_sender, sender);
   ASSERT_EQ(__total_matches, 2);
   ASSERT_EQ(__patterns.size(), 2);
   ASSERT_TRUE(__patterns.find(PatternMatcher::Pattern("he")) != __patterns.end());
   ASSERT_TRUE(__patterns.find(PatternMatcher::Pattern("his")) != __patterns.end());
   
   ASSERT_TRUE(__positions.find(4) != __positions.end());
   ASSERT_TRUE(__positions.find(21) != __positions.end());
}

#endif /* TESTS_PATTERNMATCHER_PATTERNMATCHINGMACHINE_TESTS_CPP */