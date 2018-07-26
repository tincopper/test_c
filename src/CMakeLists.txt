cmake_minimum_required(VERSION 3.5)
project(test_c C)

set(CMAKE_C_STANDARD 99)

#add_subdirectory(src)
#add_subdirectory(common)
#add_subdirectory(include)

#add_executable(test_c main.c)

#include_directories(${PROJECT_SOURCE_DIR}/common)
#include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${INCLUDE_DIRECTORIES} cJson.h ../include/cJSON.c)

add_executable(test_c
        ../include/cJSON.c main.c)
# m: lm
target_link_libraries(test_c -lm)