/* 
 * File:   Bin.hpp
 * Author: user
 *
 * Created on 28 September 2018, 10:38 AM
 */

#define BOOST_TEST_DYN_LINK 

#include "../../src/PatternMatcher/Pattern.hpp" 
#include <string>
#include <boost/test/unit_test.hpp>
 
BOOST_AUTO_TEST_CASE(test_pattern_constructors)
{
    std::string testing_string("TEST");
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(obj);
    PatternMatcher::Pattern cstr("TEST");
    
    BOOST_CHECK(obj.get_value() == testing_string); 
    BOOST_CHECK(obj == other);
    BOOST_CHECK(obj == cstr);
}

BOOST_AUTO_TEST_CASE(test_pattern_assignment_operators)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(obj);
    
    obj = other_string;
    BOOST_CHECK(obj.get_value() == other_string); 
    BOOST_CHECK(obj.get_value() != testing_string);
    
    obj = testing_string;
    BOOST_CHECK(obj.get_value() == testing_string); 
    BOOST_CHECK(obj.get_value() != other_string);
}

BOOST_AUTO_TEST_CASE(test_pattern_equality_operators)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Pattern obj(testing_string);
    PatternMatcher::Pattern other(other_string);
    
    BOOST_CHECK(other < obj);
    BOOST_CHECK(obj != other);
    obj = other;
    BOOST_CHECK(obj == other);  
} 