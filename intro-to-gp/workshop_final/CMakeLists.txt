cmake_minimum_required(VERSION 4.0)

# package search paths
if ($ENV{VCPKG_ROOT}) 
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "vcpkg toolchain file")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../third-party")

project(GPIntro)


set(CMAKE_CXX_STANDARD 20)

file(GLOB SRC_FILES src/**.cpp)

function(add_third_party)
    set(options)
    set(oneValueArgs PACKAGE HEADER LIBRARY)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message(STATUS "Looking for ${ARG_PACKAGE} in third-party")
    if(ARG_HEADER)

        find_path(
            ${ARG_PACKAGE}_INCLUDE_DIR 
            NAMES ${ARG_HEADER} 
            PATHS "${CMAKE_SOURCE_DIR}/../third-party/include" 
            NO_DEFAULT_PATH
        )
    endif()

    if(ARG_LIBRARY)
        find_library(
            ${ARG_PACKAGE}_LIBRARY
            NAMES ${ARG_LIBRARY}
            PATHS "${CMAKE_SOURCE_DIR}/../third-party/lib"
            NO_DEFAULT_PATH
        )
    endif()
    message(STATUS  ${${ARG_PACKAGE}_INCLUDE_DIR} ${${ARG_PACKAGE}_LIBRARY})
    if(${ARG_PACKAGE}_INCLUDE_DIR AND
        (NOT ARG_LIBRARY OR ${ARG_PACKAGE}_LIBRARY))

        message(STATUS "Found in ${ARG_PACKAGE} in third-party/")
        add_library(${ARG_PACKAGE} INTERFACE IMPORTED)
        target_include_directories(${ARG_PACKAGE} INTERFACE ${${ARG_PACKAGE}_INCLUDE_DIR})
        if (${ARG_PACKAGE}_LIBRARY)
            target_link_libraries(${ARG_PACKAGE} INTERFACE ${${ARG_PACKAGE}_LIBRARY})
        endif()

        set(${ARG_PACKAGE}_FOUND TRUE PARENT_SCOPE)
    else()
        message(FATAL_ERROR "${ARG_PACKAGE} not found in system or third-party/")
    endif()


endfunction()

find_package(OpenGL REQUIRED)

find_package(glfw3 QUIET)
if (NOT glfw3_FOUND)
    add_third_party(PACKAGE glfw3 HEADER GLFW/glfw3.h LIBRARY glfw3.lib)
endif()

find_package(GLEW QUIET)
if (NOT GLEW_FOUND)
    add_third_party(PACKAGE GLEW::glew HEADER GL/glew.h LIBRARY glew32s.lib)
endif()

find_package(glm QUIET)
if (NOT glm_FOUND)
    add_third_party(PACKAGE glm::glm HEADER glm/glm.hpp)
endif()

add_executable(hello_GP ${SRC_FILES})

target_link_libraries(hello_GP PRIVATE OpenGL::GL)
target_link_libraries(hello_GP PRIVATE glfw3)
target_link_libraries(hello_GP PRIVATE GLEW::glew)
target_link_libraries(hello_GP PRIVATE glm::glm)

target_compile_definitions(hello_GP PRIVATE GLEW_STATIC)

target_include_directories(hello_GP PRIVATE "src")
