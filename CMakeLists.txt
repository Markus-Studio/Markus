cmake_minimum_required(VERSION 3.0.0)
project(markus VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_BINARY "Build markus binary" ON)
option(BUILD_TESTS "Build test programs" OFF)
option(BUILD_FOR_COVERAGE "Build to be used with llvm-cov" OFF)

include_directories(include)

file(GLOB_RECURSE BIN_CPP_FILES "src/*/**.cpp")
file(GLOB_RECURSE TEST_CPP_FILES "test/*/**.cpp")
file(GLOB_RECURSE DUMPER_CPP_FILES "suit/dumper/**.cpp")

if(BUILD_BINARY)
    add_executable(markus src/main.cpp ${BIN_CPP_FILES})
endif(BUILD_BINARY)

if(BUILD_TESTS)
    add_executable(markus-test test/test.cpp ${BIN_CPP_FILES} ${TEST_CPP_FILES})
    add_executable(markus-dump suite/dumper/main.cpp ${BIN_CPP_FILES} ${DUMPER_CPP_FILES})
endif(BUILD_TESTS)

if(BUILD_FOR_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif(BUILD_FOR_COVERAGE)