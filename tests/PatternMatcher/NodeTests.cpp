/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#define BOOST_TEST_DYN_LINK 

#include "../../src/PatternMatcher/Node.hpp" 
#include "../../src/PatternMatcher/Pattern.hpp" 
#include <set>
#include <string>
#include <boost/test/unit_test.hpp>
 
BOOST_AUTO_TEST_CASE(test_node_constructors)
{ 
    PatternMatcher::Node<PatternMatcher::Pattern> obj('a'); 
    
    BOOST_CHECK(obj.get_value() == 'a');
}

BOOST_AUTO_TEST_CASE(test_node_failure)
{ 
    PatternMatcher::Node<PatternMatcher::Pattern> obj('a'); 
    PatternMatcher::Node<PatternMatcher::Pattern> failure('a'); 
    
    BOOST_CHECK(obj.get_failure() == nullptr);
    obj.set_failure(&failure);
    BOOST_CHECK(obj.get_failure() == &failure);
}

BOOST_AUTO_TEST_CASE(test_node_output)
{ 
    PatternMatcher::Pattern pattern("TEST"); 
    PatternMatcher::Node<PatternMatcher::Pattern> node('a'); 
    BOOST_CHECK(node.get_output().size() == 0);
    
    node.add_output(pattern);
    BOOST_CHECK(node.get_output().size() == 1);
    
    std::set<PatternMatcher::Pattern> set; 
    PatternMatcher::Pattern pattern2("TEST2"); 
    PatternMatcher::Pattern pattern3("TEST3"); 
    set.insert(pattern2);
    set.insert(pattern3);
    node.add_output(set);
    BOOST_CHECK(node.get_output().size() == 3);
}

BOOST_AUTO_TEST_CASE(test_node_states)
{ 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a'); 
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('b'); 
    PatternMatcher::Node<PatternMatcher::Pattern>* c = new PatternMatcher::Node<PatternMatcher::Pattern>('c'); 
     
    BOOST_CHECK(a.get_states().size() == 0);
    a.get_states()[b->get_value()] = b;
    BOOST_CHECK(a.get_states().size() == 1);
    a.get_states()[c->get_value()] = c;
    BOOST_CHECK(a.get_states().size() == 2);
    a.get_states()[c->get_value()] = c;
    BOOST_CHECK(a.get_states().size() == 2);
    
    a.clear();
    BOOST_CHECK(a.get_states().size() == 0); 
}

BOOST_AUTO_TEST_CASE(test_node_operators)
{ 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a'); 
    PatternMatcher::Node<PatternMatcher::Pattern> b('b');
    
    BOOST_CHECK(a < b); 
}

BOOST_AUTO_TEST_CASE(test_node_g)
{ 
    PatternMatcher::Node<PatternMatcher::Pattern> a('a'); 
    PatternMatcher::Node<PatternMatcher::Pattern>* b = new PatternMatcher::Node<PatternMatcher::Pattern>('b'); 
    PatternMatcher::Node<PatternMatcher::Pattern>* c = new PatternMatcher::Node<PatternMatcher::Pattern>('c'); 
    
    a.get_states()[b->get_value()] = b; 
    a.get_states()[c->get_value()] = c;
    
    BOOST_CHECK(a.g('b') == b); 
    BOOST_CHECK(a.g('c') == c); 
    BOOST_CHECK(a.g('f') == nullptr); 
    a.clear();
}