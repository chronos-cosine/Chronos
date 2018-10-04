# finds boost, triggers an error otherwise
find_package(Boost REQUIRED)
if(Boost_FOUND) 
    file(GLOB PatternMatcher_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.h" 
    )
 
    include_directories(${Boost_INCLUDE_DIRS}) 
    # creates the library 
    add_library("libChronos-PatternMatcher" STATIC ${PatternMatcher_SOURCES})
endif()