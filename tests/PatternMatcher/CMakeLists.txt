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
                          ${CHRONOS_OUTPUT_DIRECTORY}/libs/$<TARGET_FILE_NAME:libChronos-PatternMatcher>)

    add_custom_command(TARGET ${PROJECT_TEST_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E 
                copy $<TARGET_FILE:${PROJECT_TEST_NAME}>
                ${CHRONOS_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:${PROJECT_TEST_NAME}>
    )
endif()