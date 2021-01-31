include(Utils/CMake/sourcegroup.cmake)

cmake_minimum_required(VERSION 3.19)
project(TEngine)

##### API Options
option(API_OPENGL "Build with opengl suport" ON)
option(API_DIRECTX "Build with directx suport" OFF)

if((NOT API_OPENGL AND NOT API_DIRECTX) OR (API_OPENGL AND API_DIRECTX))
    message(FATAL_ERROR "API_OPENGL and API_DIRECTX cannot both be ON or OFF")
endif()

#### END API Options

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    conan_basic_setup(TARGETS)

    add_compile_definitions(-D TE_WINDOWS)
    add_compile_definitions(-D _WIN32_WINDOWS)
    add_compile_definitions(-D WIN32_LEAN_AND_MEAN)
    add_compile_definitions(-D _HAS_ITERATOR_DEBUGGING=0)
    add_compile_definitions(-D _CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(-D NOMINMAX)
    if(API_OPENGL)
        add_compile_definitions(-D TE_OPENGL)
    elseif(API_DIRECTX)
        add_compile_definitions(-D TE_DX11)
    endif()
    add_compile_options("/std:c++17")
elseif(UNIX)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)

    add_compile_options(-Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0)
    add_compile_definitions(TE_LINUX TE_OPENGL)
endif()

add_subdirectory(Code)
