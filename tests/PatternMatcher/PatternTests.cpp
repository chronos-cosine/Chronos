/* 
 * File:   PatternTests.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP
#define TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP

#include <gtest/gtest.h>
#include <string>

#include "../../src/PatternMatcher/Pattern.hpp" 

TEST(PatternMatcherTests, test_pattern_hasher) {
    PatternMatcher::Pattern pattern("TEST");
    PatternMatcher::Pattern::Hasher hasher;
    boost::hash<std::string> hash; 
    
    ASSERT_EQ(hasher(pattern), hash("TEST"));
}

TEST(PatternMatcherTests, test_pattern_constructor_char) { 
    PatternMatcher::Pattern pattern("PATTERN");
    ASSERT_EQ(pattern.get_value(), "PATTERN"); 
}

TEST(PatternMatcherTests, test_pattern_constructor_string) {
    std::string test("PATTERN");
    PatternMatcher::Pattern pattern(test);
    ASSERT_EQ(pattern.get_value(), test); 
}

TEST(PatternMatcherTests, test_pattern_constructor_cpy) { 
    PatternMatcher::Pattern test("PATTERN");
    PatternMatcher::Pattern pattern(test);
    ASSERT_EQ(pattern.get_value(), "PATTERN"); 
}

TEST(PatternMatcherTests, test_pattern_begin_end) { 
    PatternMatcher::Pattern pattern("PATTERN");
    ASSERT_NE(pattern.begin(), pattern.end()); 
}

TEST(PatternMatcherTests, test_pattern_get_value) { 
    PatternMatcher::Pattern pattern("PATTERN");
    ASSERT_EQ(pattern.get_value(), "PATTERN"); 
}

TEST(PatternMatcherTests, test_pattern_operator_string_assign) { 
    PatternMatcher::Pattern pattern("PATTERN");
    std::string n("NEW_TEST");
    pattern = n;
    ASSERT_NE(pattern.get_value(), "PATTERN");
    ASSERT_EQ(pattern.get_value(), n); 
}

TEST(PatternMatcherTests, test_pattern_operator_char_assign) { 
    PatternMatcher::Pattern pattern("PATTERN"); 
    pattern = "NEW_TEST";
    ASSERT_NE(pattern.get_value(), "PATTERN");
    ASSERT_EQ(pattern.get_value(), "NEW_TEST"); 
}

TEST(PatternMatcherTests, test_pattern_operator_pattern_assign) { 
    PatternMatcher::Pattern pattern("PATTERN"); 
    PatternMatcher::Pattern n("NEW_TEST"); 
    pattern = n;
    ASSERT_NE(pattern.get_value(), "PATTERN");
    ASSERT_EQ(pattern, n); 
}

TEST(PatternMatcherTests, test_pattern_operator_pattern_lt) { 
    PatternMatcher::Pattern a("PATTERN1"); 
    PatternMatcher::Pattern b("PATTERN2");  
    
    ASSERT_LT(a, b); 
}

TEST(PatternMatcherTests, test_pattern_operator_pattern_eq) {
    
    PatternMatcher::Pattern a("PATTERN1"); 
    PatternMatcher::Pattern b("PATTERN2");  
    PatternMatcher::Pattern c("PATTERN1"); 
    
    ASSERT_NE(a, b);
    ASSERT_EQ(a, c); 
}

TEST(PatternMatcherTests, test_pattern_operator_pattern_eq_string) {
    
    PatternMatcher::Pattern a("PATTERN1"); 
    std::string b("PATTERN2");  
    std::string c("PATTERN1"); 
    
    ASSERT_NE(a, b);
    ASSERT_EQ(a, c); 
}


#endif /* TESTS_PATTERNMATCHER_PATTERN_TESTS_CPP */