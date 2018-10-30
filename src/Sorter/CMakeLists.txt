# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    set (Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Chronos-Sorter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Bin.h"
        "${CMAKE_CURRENT_LIST_DIR}/Bin.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/BooleanOperator.h"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.h"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.h"
        "${CMAKE_CURRENT_LIST_DIR}/Settings.cpp"
        "${CHRONOS_SOURCE_ROOT}/File/DataReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/DataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/Node.h"
        "${CHRONOS_SOURCE_ROOT}/PatternMatcher/PatternMatchingMachine.h"
    )
    
    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          Boost::filesystem)
endif()