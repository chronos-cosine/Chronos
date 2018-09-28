# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if(Boost_FOUND)
    set(PROJECT_TEST_NAME "Pattern_Matcher_Unit_Tests")
    set(Boost_USE_STATIC_LIBS ON)
    include_directories(${Boost_INCLUDE_PATH}) 
    file(GLOB PatternMatcher_TEST_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
    )
    add_executable(${PROJECT_TEST_NAME} ${PatternMatcher_TEST_SOURCES})
    target_link_libraries(${PROJECT_TEST_NAME} 
                          ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} 
                          ${CMAKE_BINARY_DIR}/lib/$<TARGET_FILE_NAME:libChronos-PatternMatcher>)
endif()