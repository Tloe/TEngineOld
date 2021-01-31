include(Utils/CMake/sourcegroup.cmake)

cmake_minimum_required(VERSION 3.19)
project(TEngine)

##### API Options
option(API_OPENGL "Build with opengl suport" ON)
option(API_DIRECTX "Build with directx suport" OFF)

if((NOT API_OPENGL AND NOT API_DIRECTX) OR (API_OPENGL AND API_DIRECTX))
    message(FATAL_ERROR "API_OPENGL and API_DIRECTX cannot both be ON or OFF")
endif()

if(API_OPENGL)
    set(API_COMPILE_DEFENITION TE_OPENGL)
elseif(API_OPENGL)
    set(API_COMPILE_DEFENITION TE_DX11)
endif()

#### END API Options
#### Platform

if(WIN32)
    if(NOT MSVC)
        message(FATAL_ERROR "MSVC Compiling only on windows for now.")
    endif()
    set(COMPILE_DEFENITIONS(
        TE_WINDOWS
        _WIN32_WINDOWS
        WIN32_LEAN_AND_MEAN
        _HAS_ITERATOR_DEBUGGING=0
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
        API_COMPILE_DEFENITION)
elseif(UNIX)

else()
    message(FATAL_ERROR "Not supported on this platform")
endif()

### END Platform

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
    conan_basic_setup(TARGETS)

    add_compile_definitions(TE_WINDOWS)
    add_compile_definitions(_WIN32_WINDOWS)
    add_compile_definitions(WIN32_LEAN_AND_MEAN)
    add_compile_definitions(_HAS_ITERATOR_DEBUGGING=0)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(NOMINMAX)
    add_compile_definitions(API_COMPILE_DEFENITION)
    add_compile_options("/std:c++17")
elseif(UNIX)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)

    add_compile_options(-Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0)
    add_compile_definitions(TE_LINUX)
    add_compile_definitions(API_COMPILE_DEFENITION)
endif()

add_subdirectory(Code)
