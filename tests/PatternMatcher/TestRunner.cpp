#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "PatternTests.hpp"
#include "MatchFoundSignalArgsTests.hpp"

void 
init_pattern_tests(boost::shared_ptr<PatternTests> pattern_tests)
{
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &PatternTests::test_pattern_constructors, pattern_tests )));
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &PatternTests::test_pattern_assignment_operators, pattern_tests )));
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &PatternTests::test_pattern_equality_operators, pattern_tests )));
}
  
void 
init_matchfoundsignalargs_tests(boost::shared_ptr<MatchFoundSignalArgsTests> matchfoundsignalargs_tests)
{
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &MatchFoundSignalArgsTests::test_matchfoundsignalargs_constructors, matchfoundsignalargs_tests ))); 
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &MatchFoundSignalArgsTests::test_matchfoundsignalargs_input, matchfoundsignalargs_tests ))); 
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &MatchFoundSignalArgsTests::test_matchfoundsignalargs_position, matchfoundsignalargs_tests ))); 
    boost::unit_test::framework::master_test_suite().
        add( BOOST_TEST_CASE( boost::bind( &MatchFoundSignalArgsTests::test_matchfoundsignalargs_patterns, matchfoundsignalargs_tests ))); 
}

boost::unit_test::test_suite* 
init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{
    boost::shared_ptr<PatternTests> pattern_tests( new PatternTests ); 
    init_pattern_tests(pattern_tests);
    
    boost::shared_ptr<MatchFoundSignalArgsTests> matchfoundsignalargs_tests( new MatchFoundSignalArgsTests );
    init_matchfoundsignalargs_tests(matchfoundsignalargs_tests);
      
    return 0;
}