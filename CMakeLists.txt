cmake_minimum_required(VERSION 3.19)
project(TEngine)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TEngine_SOURCE_DIR}/Executables")


if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake" 
                 TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if(MSVC)
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP CMAKE_TARGETS
                    BUILD missing)
else()
    conan_cmake_run(CONANFILE conanfile.txt
                    BUILD_TYPE "None"
                    BASIC_SETUP CMAKE_TARGETS
                    SETTINGS compiler.libcxx=libc++
                    BUILD missing)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Utils/CMake)

if(MSVC)
    add_compile_definitions(-D TE_WINDOWS)
    add_compile_definitions(-D _WIN32_WINDOWS)
    add_compile_definitions(-D WIN32_LEAN_AND_MEAN)
    add_compile_definitions(-D _HAS_ITERATOR_DEBUGGING=0)
    add_compile_definitions(-D _CRT_SECURE_NO_WARNINGS)
    add_compile_definitions(-D NOMINMAX)
    if(Config_API STREQUAL "OpenGL")
        add_compile_definitions(-D TE_OPENGL)
    elseif(Config_API STREQUAL "DirectX")
        add_compile_definitions(-D TE_DX11)
    endif()
    add_compile_options("/std:c++17")
elseif(UNIX)
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0")
    add_compile_options(-Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0)
    add_compile_definitions(TE_LINUX TE_OPENGL)
endif()

add_subdirectory(Code)
