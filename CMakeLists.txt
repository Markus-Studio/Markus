cmake_minimum_required(VERSION 3.0.0)
project(markus VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_FOR_COVERAGE "Build to be used with llvm-cov" OFF)

include_directories(include)

file(GLOB_RECURSE LIB_CPP_FILES "src/*/**.cpp")
file(GLOB_RECURSE TEST_CPP_FILES "test/**.cpp")

add_executable(markus src/main.cpp)
add_executable(markus-test ${TEST_CPP_FILES})
add_executable(markus-dump suite/dumper/main.cpp)

# Link executables with libmar
add_library(mar STATIC ${LIB_CPP_FILES})
target_link_libraries(markus mar)
target_link_libraries(markus-test mar)
target_link_libraries(markus-dump mar)

if(BUILD_FOR_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif(BUILD_FOR_COVERAGE)