# finds boost, triggers an error otherwise
find_package(Boost REQUIRED)
if(Boost_FOUND)
    file(GLOB PatternMatcher_src
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.hpp" 
    )
    include_directories(${Boost_INCLUDE_DIRS})
 
    # creates the executable
    add_executable("PatternMatcher" ${PatternMatcher_src}) 
    add_library("Chronos-PatternMatcher" ${PatternMatcher_src})  
endif()