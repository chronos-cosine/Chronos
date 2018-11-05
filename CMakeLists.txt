##
 # To change this license header, choose License Headers in Project Properties.
 # To change this template file, choose Tools | Templates
 # and open the template in the editor.
 ##

##
 # File:   CMakeLists.txt
 # Author: Chronos Cosine <chronos.cosine@gmail.com>
 #
 # Created on 30 October 2018, 10:52 PM
 ##

#  /===============================================================\ 
# ||======================== PROJECT CHRONOS ======================|| 
#  \===============================================================/

# ================ CMAKE SETTINGS ================
# Minimum allowed version of CMake is 2.8
cmake_minimum_required(VERSION 3.7.2)

# Set the project name
project(Chronos)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ================ VERSIONING ====================
set(CHRONOS_VERSION_MAJOR 0)
set(CHRONOS_VERSION_MINOR 1)
set(CHRONOS_VERSION_PATCH 1)

# ================ MAIN OBJECTS ==================
set(CMAKE_CXX_FLAGS "-std=c++17 -pthread")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# ================ MAIN SOURCE =========================
add_subdirectory(src)