cmake_minimum_required(VERSION 3.8)
project(px_jvm)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/vm)
include_directories(src/vm/oops)
include_directories(src/vm/utilities)
include_directories(src/vm/interpreter)
include_directories(src/vm/classfile)
include_directories(src/vm/adlc)

file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*/*.cc
        ${PROJECT_SOURCE_DIR}/src/*/*.hh
        ${PROJECT_SOURCE_DIR}/src/*/*/*.cc
        ${PROJECT_SOURCE_DIR}/src/*/*/*.hh
        )

add_executable(px_jvm ${SOURCE_FILES} src/main.cc)
