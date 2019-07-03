cmake_minimum_required(VERSION 3.0)

set(NAME fractals-2d)

add_library(${NAME} fractals_2d.cpp)

target_include_directories(${NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/include/${NAME}"
        PRIVATE "${PROJECT_SOURCE_DIR}/sources/${NAME}")

target_link_libraries(${NAME} opengl)
