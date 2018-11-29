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
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/Node.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/PatternMatchingMachine.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/ProcessorBase.cpp"
        "${CHRONOS_SOURCE_ROOT}/Processors/ProcessorBase.h"
        "${CMAKE_CURRENT_LIST_DIR}/Data/DataContext.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Data/DataContext.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Bin.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Bin.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/BooleanOperator.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Job.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Job.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Pattern.h"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Result.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Models/Result.h"
        "${CMAKE_CURRENT_LIST_DIR}/Repositories/CsvFileDataRepository.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Repositories/CsvFileDataRepository.h"
        "${CMAKE_CURRENT_LIST_DIR}/Repositories/IDataRepository.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/IDataProvider.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/IDataValidator.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataProviders/MultiPatternMatcher.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataProviders/MultiPatternMatcher.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataProviders/PatternlessBinDataProvider.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataProviders/PatternlessBinDataProvider.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/AndDataValidator.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/AndDataValidator.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/HierarchyValidator.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/HierarchyValidator.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/NotDataValidator.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/NotDataValidator.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/OrDataValidator.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/DataValidators/OrDataValidator.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/SortingMachine.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/SortingMachine.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Services/SortingProcess.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Services/SortingProcess.h" 
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          stdc++fs
                          Boost::filesystem)
endif()