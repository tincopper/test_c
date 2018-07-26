cmake_minimum_required(VERSION 3.5)
project(test_c C)

set(CMAKE_C_STANDARD 99)

add_library(${INCLUDE_DIRECTORIES} cJson.h ../include/cJSON.c)
add_library(${INCLUDE_DIRECTORIES} host_info.h ../include/host_info.c)

add_executable(test_c
        ../include/host_info.c
        ../include/cJSON.c
        main.c )
# m: lm
target_link_libraries(test_c -lm)