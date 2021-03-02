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
    set(COMPILE_DEFENITIONS
        TE_WINDOWS
        _WIN32_WINDOWS
        WIN32_LEAN_AND_MEAN
        _HAS_ITERATOR_DEBUGGING=0
        _CRT_SECURE_NO_WARNINGS
        NOMINMAX
        ${API_COMPILE_DEFENITION})
    set(COMPILE_OPTS "/std:c++17")
    include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
elseif(UNIX)
    set(COMPILE_DEFENITIONS
        TE_LINUX
        ${API_COMPILE_DEFENITION})
    set(COMPILE_OPTS
      -Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
else()
    message(FATAL_ERROR "Not supported on this platform")
endif()

### END Platform

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_compile_definitions(${COMPILE_DEFENITIONS})
add_compile_options(${COMPILE_OPTS})

conan_basic_setup(TARGETS)

add_subdirectory(Code)
