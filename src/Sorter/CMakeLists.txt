# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    set (Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Bin.h"
        "${CMAKE_CURRENT_LIST_DIR}/Bin.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/BooleanOperator.h"
        "${CMAKE_CURRENT_LIST_DIR}/Chronos-Sorter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Job.h"
        "${CMAKE_CURRENT_LIST_DIR}/Job.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.h"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.h"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/SortingMachine.h"
        "${CMAKE_CURRENT_LIST_DIR}/SortingMachine.cpp"
        "${CHRONOS_SOURCE_ROOT}/Collections/ConcurrentQueue.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ConcurrentStack.h"
        "${CHRONOS_SOURCE_ROOT}/Collections/ICollection.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/File/DataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/Node.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/PatternMatchingMachine.h"
    )
    
    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          Boost::filesystem)
endif()