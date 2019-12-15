cmake_minimum_required(VERSION 3.0.0)
project(markus VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB_RECURSE BIN_CPP_FILES "src/*/**.cpp")
file(GLOB_RECURSE TEST_CPP_FILES "tests/*.cpp")

add_executable(markus src/main.cpp ${BIN_CPP_FILES})
add_executable(markus-test ${BIN_CPP_FILES} ${TEST_CPP_FILES})

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
