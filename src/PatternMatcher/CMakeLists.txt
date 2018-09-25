file(GLOB PatternMatcher_src
        "${CMAKE_CURRENT_LIST_DIR}/CompletedSignalArgs.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/CompletedSignalArgs.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/IdeablePattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/IdeablePattern.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/MatchFoundSignalArgs.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/MatchFoundSignalArgs.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/Node.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Node.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Pattern.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/PatternMatchingMachine.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/PatternMatchingMachine.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/Program.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/RootNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/RootNode.hpp"
)

add_executable (Chronos-PatternMatcher ${PatternMatcher_src})
