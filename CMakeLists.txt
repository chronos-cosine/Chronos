#  /===============================================================\ 
# ||======================== PROJECT CHRONOS ======================|| 
#  \===============================================================/

# ================ CMAKE SETTINGS ================
# Minimum allowed version of CMake is 2.8
cmake_minimum_required(VERSION 2.8)
# Set the project name
project(Chronos)

# ================ VERSIONING ====================
set(CHRONOS_VERSION_MAJOR 0)
set(CHRONOS_VERSION_MINOR 1)
set(CHRONOS_VERSION_PATCH 1)

# ================ MAIN OBJECTS ==================
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
add_subdirectory(src)
 
# ================ TESTS =========================
add_subdirectory(tests)
