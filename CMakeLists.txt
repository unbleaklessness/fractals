cmake_minimum_required(VERSION 3.0)

set(MY_PROJECT_NAME fractals)
project(${MY_PROJECT_NAME})

# Git submodules:
option(GIT_SUBMODULE "Check submodules during build" ON)
if(GIT_SUBMODULE)
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        message(STATUS "Submodules updating")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "Failed to update Git submodules!")
        endif()
    else()
        message(STATUS "Could not find Git executable or Git project!")
    endif()
endif()

# Doxygen:
option(BUILD_DOC "Build documentation" ON)
if(BUILD_DOC)
    find_package(Doxygen QUIET)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN "${PROJECT_SOURCE_DIR}/Doxyfile")
        set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

        configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

        add_custom_target(doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYGEN_OUT}"
                WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
    else()
        message(STATUS "Doxygen need to be installed to generate the Doxygen documentation!")
    endif()
endif()

enable_testing()

add_subdirectory(sources)
add_subdirectory(tests)
add_subdirectory(apps)
add_subdirectory(extern)