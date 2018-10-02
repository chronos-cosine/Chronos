include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB PatternMatcher_UnitTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/../../src/PatternMatcher/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../../src/PatternMatcher/*.hpp"
)
# Link runTests with what we want to test and the GTest and pthread library
add_executable("Pattern_Matcher_Unit_Tests" ${PatternMatcher_UnitTests_SOURCES})
target_link_libraries("Pattern_Matcher_Unit_Tests"
                      ${GTEST_LIBRARIES} -lpthread)
