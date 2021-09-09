cmake_minimum_required(VERSION 3.17)
project(compiler_vm)

set(CMAKE_CXX_STANDARD 20)

# CTest
enable_testing()


# Includes.
set(PX_JVM_SRC_INCLUDE_DIR 
    ${PROJECT_SOURCE_DIR}/src/vm/oops 
    ${PROJECT_SOURCE_DIR}/src/vm/utilities
    ${PROJECT_SOURCE_DIR}/src/vm/interpreter
    ${PROJECT_SOURCE_DIR}/src/vm/adlc
    ${PROJECT_SOURCE_DIR}/src/vm/classfile
    )
set(PX_JVM_TEST_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/tests/include)
set(PX_JVM_THIRD_PARTY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/ext/gtest/googletest ${PROJECT_SOURCE_DIR}/ext/fmt/include)
include_directories(${PX_JVM_SRC_INCLUDE_DIR} ${PX_JVM_TEST_INCLUDE_DIR} ${PX_JVM_THIRD_PARTY_INCLUDE_DIR})
# include_directories(BEFORE src) # This is needed for gtest.

add_subdirectory(ext/fmt)
add_subdirectory(ext/gtest)
add_subdirectory(src)
add_subdirectory(test)
