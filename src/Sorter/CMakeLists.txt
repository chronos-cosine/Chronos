file(GLOB Sorter_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.h" 
)

# creates the library 
add_executable(Chronos-Sorter ${Sorter_SOURCES})

target_link_libraries(Chronos-Sorter
                      ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:libChronos-PatternMatcher>)
