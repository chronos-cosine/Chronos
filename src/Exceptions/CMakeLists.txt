file(GLOB Core_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/*.h" 
)
# creates the library 
add_library(libChronos-Exceptions ${Core_SOURCES})
