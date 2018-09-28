# finds boost, triggers an error otherwise
find_package(Boost REQUIRED filesystem)
if(Boost_FOUND)
    set(PATTERN_MATCHER_OUTPUT_NAME "Chronos-PatternMatcher")
    file(GLOB PatternMatcher_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.hpp" 
    )

    # creates the executable
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(${PATTERN_MATCHER_OUTPUT_NAME} ${PatternMatcher_SOURCES})
     
    # creates the library
    list(REMOVE_ITEM PatternMatcher_SOURCES "Program.cpp")
    add_library("lib${PATTERN_MATCHER_OUTPUT_NAME}" STATIC ${PatternMatcher_SOURCES})
endif()