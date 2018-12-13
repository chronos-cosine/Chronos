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
find_package(OpenCV REQUIRED COMPONENTS core imgproc highgui)
if(Boost_FOUND) 
    set (LogoRecognition_SOURCES 
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/INotifier.h"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    include_directories(${OpenCV_INCLUDE_DIRS})
    add_executable(Chronos-LogoRecognition ${LogoRecognition_SOURCES})

    target_link_libraries(Chronos-LogoRecognition
                          stdc++fs
                          Boost::filesystem
                          ${OpenCV_LIBS})
endif()