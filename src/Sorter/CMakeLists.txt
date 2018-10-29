# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    set (Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Chronos-Sorter.cpp"
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