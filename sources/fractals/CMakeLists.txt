cmake_minimum_required(VERSION 3.0)

set(NAME fractals)

add_library(${NAME} fractals.cpp)

target_include_directories(${NAME}
        PUBLIC "${PROJECT_SOURCE_DIR}/include/${NAME}"
        PRIVATE "${PROJECT_SOURCE_DIR}/sources/${NAME}")
