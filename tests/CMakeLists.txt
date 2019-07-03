cmake_minimum_required(VERSION 3.0)

set(NAME tests)

add_executable(${NAME} main.cpp fractals-2d/fractals_2d_test.h)

target_include_directories(${NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${NAME} fractals-2d)