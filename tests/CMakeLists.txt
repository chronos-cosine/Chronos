find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# ================ PATTERN MATCHER =========================  
file(GLOB Chronos_UnitTests_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/PatternMatcher/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PatternMatcher/*.hpp"
)
# Link runTests with what we want to test and the GTest and pthread library
add_executable("Chronos_Unit_Tests" ${Chronos_UnitTests_SOURCES})
target_link_libraries("Chronos_Unit_Tests"
                      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:libChronos-PatternMatcher>
                      ${GTEST_LIBRARIES} -lpthread)