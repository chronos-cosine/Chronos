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
if (Boost_FOUND) 
    set (PDF_Rasterisor_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS})  
    add_executable(Chronos-Pdf-Rasterisor ${PDF_Rasterisor_SOURCES})

    target_link_libraries(Chronos-Pdf-Rasterisor
                          podofo
                          stdc++fs
                          Boost::filesystem) 
endif()