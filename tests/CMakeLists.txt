cmake_minimum_required(VERSION 3.0)

set(NAME tests)

add_executable(${NAME} main.cpp fractals/fractals_test.h)

target_include_directories(${NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${NAME} fractals)