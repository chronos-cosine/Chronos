# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    file(GLOB Core_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.h" 
    )

    # creates the library 
    add_library(libChronos-Processors ${Core_SOURCES})
endif()


