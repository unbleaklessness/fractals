cmake_minimum_required(VERSION 3.0)

set(NAME 3d-mandelbrot)

add_executable(${NAME} main.cpp)

add_dependencies(${NAME} freeglut)

target_include_directories(${NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(${NAME} PRIVATE fractals freeglut)