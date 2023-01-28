cmake_minimum_required(VERSION 3.16)

set(TARGET_NAME app)

file(GLOB_RECURSE TARGET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${TARGET_NAME} ${TARGET_SRC})

set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME csvreader)

target_link_libraries(${TARGET_NAME}
PUBLIC
    table
)
