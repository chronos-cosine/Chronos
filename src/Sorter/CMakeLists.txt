file(GLOB Sorter_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.h" 
)

# creates the library 
add_executable(Chronos-Sorter ${Sorter_SOURCES})