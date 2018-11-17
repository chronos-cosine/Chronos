##
 # To change this license header, choose License Headers in Project Properties.
 # To change this template file, choose Tools | Templates
 # and open the template in the editor.
 ##

##
 # File:   src/Sorter/CMakeLists.txt
 # Author: Chronos Cosine <chronos.cosine@gmail.com>
 #
 # Created on 30 October 2018, 10:52 PM
 ##

# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    set (Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Data/Bins.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Data/Bins.h"
        "${CMAKE_CURRENT_LIST_DIR}/Data/DataContext.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Data/DataContext.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataReader.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Bin.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Bin.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/BooleanOperator.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Pattern.h"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          stdc++fs
                          Boost::filesystem)
endif()