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
find_package (Boost REQUIRED COMPONENTS filesystem)
#find_package (podofo REQUIRED)
if (Boost_FOUND)
#    if (podofo_FOUND)
        set (Rasterisor_SOURCES
            "${CHRONOS_SOURCE_ROOT}/Geometry/Point.cpp"
            "${CHRONOS_SOURCE_ROOT}/Geometry/Point.h"
            "${CMAKE_CURRENT_LIST_DIR}/TextExtractor.cpp"
            "${CMAKE_CURRENT_LIST_DIR}/TextExtractor.h"
            "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
        )

        # creates the library 
        include_directories(${Boost_INCLUDE_DIRS}) 
#        include_directories(${Podofo_INCLUDE_DIRS}) 
        add_executable(Chronos-Rasterisor ${Rasterisor_SOURCES})

        target_link_libraries(Chronos-Rasterisor
                              podofo
                              stdc++fs
                              Boost::filesystem)
#    endif()
endif()
