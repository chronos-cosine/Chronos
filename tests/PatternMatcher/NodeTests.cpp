/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_NODE_TESTS_CPP
#define TESTS_PATTERNMATCHER_NODE_TESTS_CPP

#include <gtest/gtest.h> 
#include "../../src/PatternMatcher/Node.hpp"
#include "../../src/PatternMatcher/Pattern.hpp"

TEST(PatternMatcherTests, test_node_constructors) { 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    ASSERT_EQ(a.get_value(), 'a');
    ASSERT_EQ(a.get_failure(), nullptr);
    ASSERT_EQ(a.get_output().size(), 0);
    ASSERT_EQ(a.get_states().size(), 0);
}

#endif /* TESTS_PATTERNMATCHER_NODE_TESTS_CPP */