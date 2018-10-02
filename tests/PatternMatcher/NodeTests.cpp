/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_PATTERNMATCHER_NODE_TESTS_CPP
#define TESTS_PATTERNMATCHER_NODE_TESTS_CPP

#include <boost/functional/hash.hpp>
#include <gtest/gtest.h> 
#include "../../src/PatternMatcher/Node.hpp"
#include "../../src/PatternMatcher/Pattern.hpp"

TEST(PatternMatcherTests, test_node_hasher) {
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    PatternMatcher::Node<PatternMatcher::Pattern>::Hasher hasher;
    boost::hash<char> hash; 
    
    ASSERT_EQ(hasher(a), hash(a.get_value()));
}

TEST(PatternMatcherTests, test_node_constructor) { 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    ASSERT_EQ(a.get_value(), 'a');
    ASSERT_EQ(a.get_failure(), nullptr);
    ASSERT_EQ(a.get_output().size(), 0);
    ASSERT_EQ(a.get_states().size(), 0);
}

TEST(PatternMatcherTests, test_node_failure) { 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a'); 
    ASSERT_EQ(a.get_failure(), nullptr);
    a.set_failure(&a); 
    ASSERT_EQ(a.get_failure(), &a); 
    a.set_failure(nullptr); 
    ASSERT_EQ(a.get_failure(), nullptr);
}

TEST(PatternMatcherTests, test_node_value) { 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a'); 
    ASSERT_EQ(a.get_value(), 'a');
    PatternMatcher::Node<PatternMatcher::Pattern> b('b'); 
    ASSERT_EQ(b.get_value(), 'b');
    PatternMatcher::Node<PatternMatcher::Pattern> c('c'); 
    ASSERT_EQ(c.get_value(), 'c');
}

TEST(PatternMatcherTests, test_node_output) {
    PatternMatcher::Pattern pattern_1("pattern_1");
    std::set<PatternMatcher::Pattern> set;
    PatternMatcher::Pattern pattern_2("pattern_2");
    PatternMatcher::Pattern pattern_3("pattern_3");
    set.insert(pattern_2);
    set.insert(pattern_3);
    
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    a.add_output(pattern_1);
    ASSERT_EQ(a.get_output().size(), 1);
    a.add_output(set);
    ASSERT_EQ(a.get_output().size(), 3);
    a.add_output(pattern_1);
    ASSERT_EQ(a.get_output().size(), 3);
}

TEST(PatternMatcherTests, test_node_states) {
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('b');
    PatternMatcher::Node<PatternMatcher::Pattern>* c = new PatternMatcher::Node<PatternMatcher::Pattern>('c'); 
    
    a.add_state(b);
    ASSERT_EQ(a.get_states().size(), 1);
    a.add_state(c);
    ASSERT_EQ(a.get_states().size(), 2);
    a.add_state(c);
    ASSERT_EQ(a.get_states().size(), 2);
}
 
TEST(PatternMatcherTests, test_node_g) {
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('b');
    PatternMatcher::Node<PatternMatcher::Pattern>* c = new PatternMatcher::Node<PatternMatcher::Pattern>('c'); 
    a.add_state(b); 
    a.add_state(c);
    
    ASSERT_EQ(a.g(b->get_value()), b);
    ASSERT_EQ(a.g(c->get_value()), c);
    ASSERT_EQ(a.g('h'), nullptr);
    a.clear();
}

TEST(PatternMatcherTests, test_node_clear) {
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('b');
    PatternMatcher::Node<PatternMatcher::Pattern>* c = new PatternMatcher::Node<PatternMatcher::Pattern>('c'); 
    
    a.add_state(b); 
    a.add_state(c);
    
    ASSERT_EQ(a.get_states().size(), 2);
    a.clear();
    ASSERT_EQ(a.get_states().size(), 0);
}

TEST(PatternMatcherTests, test_node_operator_lt) {
    PatternMatcher::Node<PatternMatcher::Pattern> a('a');
    PatternMatcher::Node<PatternMatcher::Pattern> b('b');
    PatternMatcher::Node<PatternMatcher::Pattern> c('c'); 
     
    ASSERT_LT(a, b);
    ASSERT_LT(b, c);
    ASSERT_LT(a, c);
}

#endif /* TESTS_PATTERNMATCHER_NODE_TESTS_CPP */