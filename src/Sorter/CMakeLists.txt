# finds boost, triggers an error otherwise
find_package(Boost REQUIRED COMPONENTS filesystem)
if(Boost_FOUND) 
    file(GLOB Sorter_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/*.h"
        "${CMAKE_CURRENT_LIST_DIR}/File/*.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/File/*.h"
        "${CHRONOS_SOURCE_ROOT}/Core/ArgumentReader.h"
        "${CHRONOS_SOURCE_ROOT}/Core/Helpers.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/File/CsvFileReader.cpp"
        "${CHRONOS_SOURCE_ROOT}/File/CsvFileReader.h"
        "${CHRONOS_SOURCE_ROOT}/File/DataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/File/JsonDataWriter.h"
        "${CHRONOS_SOURCE_ROOT}/Exceptions/Exception.h"
        "${CHRONOS_SOURCE_ROOT}/Exceptions/Exception.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/INotifier.h" 
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/CoutNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/LogFileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.h"
        "${CHRONOS_SOURCE_ROOT}/Notifier/FileNotifier.cpp"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/IProcessor.cpp"
        "${CHRONOS_SOURCE_ROOT}/Processors/FileSpooler.h"
        "${CHRONOS_SOURCE_ROOT}/Processors/FileSpooler.cpp"
    )

    # creates the library 
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(Chronos-Sorter ${Sorter_SOURCES})

    target_link_libraries(Chronos-Sorter
                          Boost::filesystem)
endif()
