cmake_minimum_required(VERSION 3.0.0)
project(markus VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(markus
    # Files
    src/main.cpp
    src/type/atomic.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
