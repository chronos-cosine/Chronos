/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MatchFoundSignalArgsTests.cpp
 * Author: user
 * 
 * Created on 26 September 2018, 10:02 AM
 */

#include "MatchFoundSignalArgsTests.hpp" 
#include "../../src/PatternMatcher/MatchFoundSignalArgs.hpp" 
#include "../../src/PatternMatcher/Pattern.hpp" 
#include <string>
#include <set>
#include <boost/test/unit_test.hpp>
 
void 
MatchFoundSignalArgsTests::test_matchfoundsignalargs_constructors()
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern>* testing_patterns = nullptr;
    int testing_position = 4;
    
    BOOST_REQUIRE_THROW(PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern>(testing_position, 
                testing_input, 
                testing_patterns), 
            std::runtime_error); 
}

void 
MatchFoundSignalArgsTests::test_matchfoundsignalargs_input()
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, &testing_patterns);
    
    BOOST_CHECK(obj.get_input() == testing_input); 
}

void 
MatchFoundSignalArgsTests::test_matchfoundsignalargs_position()
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, 
                &testing_patterns);
    
    BOOST_CHECK(obj.get_position() == testing_position); 
}

void 
MatchFoundSignalArgsTests::test_matchfoundsignalargs_patterns()
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, 
                &testing_patterns);
    
    BOOST_CHECK(obj.get_patterns() == &testing_patterns); 
}
