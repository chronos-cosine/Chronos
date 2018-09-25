# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if(Boost_FOUND)
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_PATH}) 
    file(GLOB PatternMatcher_test
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.hpp" 
        "../../src/PatternMatcher/Pattern.cpp"
        "../../src/PatternMatcher/Pattern.hpp" 
    )
    add_executable("Pattern-Matcher-Test" ${PatternMatcher_test}) 
    target_link_libraries("Pattern-Matcher-Test" ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    add_test("Pattern-Matcher-Test" "Pattern-Matcher-Test")
endif()
 