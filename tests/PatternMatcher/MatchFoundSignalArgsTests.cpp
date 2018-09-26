#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../../src/PatternMatcher/MatchFoundSignalArgs.hpp" 
#include "../../src/PatternMatcher/Pattern.hpp" 
#include <string>
#include <set> 
#include <exception>
 
BOOST_AUTO_TEST_CASE(test_matchfoundsignalargs_constructors)
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern>* testing_patterns = nullptr;
    int testing_position = 4;
    
    BOOST_REQUIRE_THROW(PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern>(testing_position, 
                testing_input, 
                testing_patterns), 
            std::invalid_argument); 
}

BOOST_AUTO_TEST_CASE(test_matchfoundsignalargs_input)
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, &testing_patterns);
    
    BOOST_CHECK(obj.get_input() == testing_input); 
}

BOOST_AUTO_TEST_CASE(test_matchfoundsignalargs_position)
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, 
                &testing_patterns);
    
    BOOST_CHECK(obj.get_position() == testing_position); 
}

BOOST_AUTO_TEST_CASE(test_matchfoundsignalargs_patterns)
{
    std::string testing_input("TEST");
    std::set<PatternMatcher::Pattern> testing_patterns;
    int testing_position = 4;
    PatternMatcher::MatchFoundSignalArgs<PatternMatcher::Pattern> obj(testing_position, 
                testing_input, 
                &testing_patterns);
    
    BOOST_CHECK(obj.get_patterns() == &testing_patterns); 
}
