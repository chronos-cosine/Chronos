/* 
 * File:   TestRunner.cpp
 * Author: Chronos Cosine
 *
 * Created on 28 September 2018, 10:38 AM
 */

#ifndef TESTS_TESTRUNNER_CPP
#define TESTS_TESTRUNNER_CPP

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#endif /* TESTS_TESTRUNNER_CPP */