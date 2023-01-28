cmake_minimum_required(VERSION 3.16)

project(YADRO_TASK LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


#if(WIN32)
#    set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Z7 /Od")
#    option(gtest_force_shared_crt "" TRUE)
#endif()

add_subdirectory(table)
add_subdirectory(app)
add_subdirectory(thirdparty)
enable_testing()
include(GoogleTest)
add_subdirectory(tests)
