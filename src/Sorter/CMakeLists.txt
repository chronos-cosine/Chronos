# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    set (Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Bin.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Bin.h"
        "${CMAKE_CURRENT_LIST_DIR}/BooleanOperator.h"
        "${CMAKE_CURRENT_LIST_DIR}/Chronos-Sorter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Job.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Job.h"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.h"
        "${CMAKE_CURRENT_LIST_DIR}/Result.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Result.h"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.h"
        "${CMAKE_CURRENT_LIST_DIR}/Sorter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Sorter.h"
        "${CMAKE_CURRENT_LIST_DIR}/SortingMachine.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/SortingMachine.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ConcurrentQueue.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ConcurrentStack.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ICollection.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/File/DataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/File/Spooler.cpp"
        "${CHRONOS_SOURCE_ROOT}/File/Spooler.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/INotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/Notifiable.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/Notifiable.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/Node.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/PatternMatchingMachine.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.cpp"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.h"
    )
    
    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          stdc++fs
                          Boost::filesystem)
endif()