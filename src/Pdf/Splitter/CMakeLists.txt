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
    set (PDF_Splitter_SOURCES
        "${CHRONOS_SOURCE_ROOT}/Collections/Concurrent/Map.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/Concurrent/Queue.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ICollection.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/IMap.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/Spooler.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/INotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/ProcessorBase.cpp"
        "${CHRONOS_SOURCE_ROOT}/Processors/ProcessorBase.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Job.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Job.h"
        "${CMAKE_CURRENT_LIST_DIR}/Services/PdfSplitter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/PdfSplitter.h"
        "${CMAKE_CURRENT_LIST_DIR}/Services/SplittingMachine.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/SplittingMachine.h"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS})  
    add_executable(Chronos-Pdf-Splitter ${PDF_Splitter_SOURCES})

    target_link_libraries(Chronos-Pdf-Splitter
                          podofo
                          stdc++fs
                          Boost::filesystem) 
endif()

