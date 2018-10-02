find_package(GTest REQUIRED)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# ================ PATTERN MATCHER =========================
add_subdirectory(PatternMatcher)