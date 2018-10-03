/* 
 * File:   RootNodeTests.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_ROOTNODE_TESTS_CPP
#define TESTS_PATTERNMATCHER_ROOTNODE_TESTS_CPP
 
#include <gtest/gtest.h> 
#include "../../src/PatternMatcher/RootNode.hpp" 
#include "../../src/PatternMatcher/Node.hpp" 
#include "../../src/PatternMatcher/Pattern.hpp" 

TEST(PatternMatcherTests, test_rootnode_constructor) { 
    PatternMatcher::RootNode<PatternMatcher::Pattern>* a = new PatternMatcher::RootNode<PatternMatcher::Pattern>();
    
    ASSERT_EQ(((PatternMatcher::Node<PatternMatcher::Pattern>*)a)->get_value(), '~'); 
    delete a;
}

TEST(PatternMatcherTests, test_rootnode_g) { 
    PatternMatcher::RootNode<PatternMatcher::Pattern>* a = new PatternMatcher::RootNode<PatternMatcher::Pattern>();
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('a');
    
    ASSERT_EQ(a->g('a'), a); 
    
    a->add_state(b);
    
    ASSERT_EQ(a->g('a'), b);
     
    a->clear();
    delete a;
}

#endif /* TESTS_PATTERNMATCHER_ROOTNODE_TESTS_CPP */