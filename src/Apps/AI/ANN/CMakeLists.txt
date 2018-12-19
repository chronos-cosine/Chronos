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
        "${CHRONOS_SOURCE_ROOT}/AI/NeuralNetworks/ANN/IActivationFunction.h"
        "${CHRONOS_SOURCE_ROOT}/AI/NeuralNetworks/ANN/ILayer.h"
        "${CHRONOS_SOURCE_ROOT}/AI/NeuralNetworks/ANN/Layer.cpp"
        "${CHRONOS_SOURCE_ROOT}/AI/NeuralNetworks/ANN/Layer.h"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          stdc++fs
                          Boost::filesystem)
endif()