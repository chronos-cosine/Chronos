/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP
#define TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP

#include <gtest/gtest.h>
#include <string>

#include "../../src/PatternMatcher/Pattern.hpp" 

TEST(PatternMatcherTests, test_pattern_constructors) { 
    std::string testing_string("TEST");
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(obj);
    PatternMatcher::Pattern cstr("TEST");
    
    ASSERT_EQ(obj.get_value(), testing_string); 
    ASSERT_EQ(obj, other);
    ASSERT_EQ(obj, cstr); 
}

TEST(PatternMatcherTests, test_pattern_assignment_operators)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(obj);
    
    obj = other_string;
    ASSERT_EQ(obj.get_value(), other_string); 
    ASSERT_NE(obj.get_value(), testing_string);
    
    obj = testing_string;
    ASSERT_EQ(obj.get_value(), testing_string); 
    ASSERT_NE(obj.get_value(), other_string);
}

TEST(PatternMatcherTests, test_pattern_equality_operators)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(other_string);
    
    ASSERT_LT(other, obj);
    ASSERT_NE(obj, other);
    obj = other;
    ASSERT_EQ(obj, other);  
}

#endif /* TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP */