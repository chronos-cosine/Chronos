# ================ TESTING =========================
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
set(ENABLE_COVERAGE On)
# enable code coverage
find_package(codecov)
enable_testing()

# ================ PATTERN MATCHER =========================
add_subdirectory(PatternMatcher)