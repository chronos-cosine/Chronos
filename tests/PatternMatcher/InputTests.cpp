#include "../../src/PatternMatcher/Input.hpp"
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "Chronos::PatternMatcher::Input Tests"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(PatternMatcherSuite)

BOOST_AUTO_TEST_CASE(constructors)
{
    std::string testing_string("TEST");
    PatternMatcher::Input obj(testing_string);
    PatternMatcher::Input other(obj);
    
    BOOST_CHECK(obj.get_value() == testing_string); 
    BOOST_CHECK(obj == other);
}

BOOST_AUTO_TEST_CASE(assignments)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Input obj(testing_string);
    PatternMatcher::Input other(obj);
    
    obj = other_string;
    BOOST_CHECK(obj.get_value() == other_string); 
    BOOST_CHECK(obj.get_value() != testing_string);
    
    obj = testing_string;
    BOOST_CHECK(obj.get_value() == testing_string); 
    BOOST_CHECK(obj.get_value() != other_string);
}

BOOST_AUTO_TEST_CASE(equality)
{
    std::string testing_string("TEST");
    std::string other_string("OTHER");
    
    PatternMatcher::Input obj(testing_string);
    PatternMatcher::Input other(other_string);
    
    BOOST_CHECK(other < obj);
    BOOST_CHECK(obj != other);
    obj = other;
    BOOST_CHECK(obj == other); 
}

BOOST_AUTO_TEST_SUITE_END()