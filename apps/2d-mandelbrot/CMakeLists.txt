cmake_minimum_required(VERSION 3.0)

set(NAME 2d-mandelbrot)

set(OPENGL_COPY_BINARIES_PATH "${CMAKE_BINARY_DIR}/apps/${NAME}" CACHE STRING "" FORCE)

add_executable(${NAME} main.cpp)
add_dependencies(${NAME} opengl)

target_include_directories(${NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${NAME} PRIVATE fractals opengl)
