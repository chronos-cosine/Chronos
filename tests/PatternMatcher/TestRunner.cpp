#define BOOST_TEST_NO_MAIN
#include <boost/test/included/unit_test.hpp>
#include "PatternTests.hpp"
#include "MatchFoundSignalArgsTests.hpp"
 
static PatternTests pattern_tests;
static MatchFoundSignalArgsTests matchfoundsignalargs_tests;
 
static void
init_pattern_tests(boost::unit_test::test_suite* pattern_matcher_suite)
{ 
    // Add the Pattern tests
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&PatternTests::test_pattern_constructors, 
                    &pattern_tests)));
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&PatternTests::test_pattern_assignment_operators, 
                    &pattern_tests)));
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&PatternTests::test_pattern_equality_operators, 
                    &pattern_tests))); 
}

static void
init_matchfoundsignalargs_tests(boost::unit_test::test_suite* pattern_matcher_suite)
{ 
    // Add the Pattern tests
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&MatchFoundSignalArgsTests::test_matchfoundsignalargs_constructors, 
                    &matchfoundsignalargs_tests)));
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&MatchFoundSignalArgsTests::test_matchfoundsignalargs_input, 
                    &matchfoundsignalargs_tests)));
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&MatchFoundSignalArgsTests::test_matchfoundsignalargs_position, 
                    &matchfoundsignalargs_tests))); 
    pattern_matcher_suite->add(BOOST_TEST_CASE(
        boost::bind(&MatchFoundSignalArgsTests::test_matchfoundsignalargs_patterns, 
                    &matchfoundsignalargs_tests)));  
}
 
static boost::unit_test::test_suite*
init_unit_test_suite(int argc, char* argv[])
{
    boost::unit_test::test_suite* pattern_matcher_suite = BOOST_TEST_SUITE("Chronos::PatternMatcher::TestSuite");
    
    init_pattern_tests(pattern_matcher_suite); 
    init_matchfoundsignalargs_tests(pattern_matcher_suite); 
    
    boost::unit_test::framework::master_test_suite().add(pattern_matcher_suite);
    
    return 0;
}

int 
main(int argc, char* argv[])
{
    return boost::unit_test::unit_test_main(init_unit_test_suite, argc, argv);
}