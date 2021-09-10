
file(GLOB_RECURSE SOURCE_FILES
        ${PROJECT_SOURCE_DIR}/src/*/*.cc
        ${PROJECT_SOURCE_DIR}/src/*/*/*.cc
        )

add_library(px_jvm_shared SHARED ${SOURCE_FILES} )

add_executable(px_jvm ${SOURCE_FILES} ${PROJECT_SOURCE_DIR}/src/main.cc)

target_link_libraries(px_jvm fmt)
target_link_libraries(px_jvm_shared fmt)
