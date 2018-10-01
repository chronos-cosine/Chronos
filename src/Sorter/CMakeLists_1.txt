set(SORTER_OUTPUT_NAME "Chronos-PatternMatcher")
file(GLOB Sorter_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp" 
)

# creates the library 
add_library("lib${SORTER_OUTPUT_NAME}" STATIC ${Sorter_SOURCES})