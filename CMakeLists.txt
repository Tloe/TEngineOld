cmake_minimum_required(VERSION 3.13)
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

#conan_add_remote(NAME luajit-rocks 
#                 URL https://github.com/gsage/conan-luajit-rocks
#                 VERIFY_SSL True)

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#if(MSVC)
#	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "9. CMake")
		
#	set(CMAKE_CONFIGURATION_TYPES "DebugOpenGL;ReleaseOpenGL;DebugDX11;ReleaseDX11")
#	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
#		"Reset the configurations to what we need"
#		FORCE)
#	set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS DebugOpenGL DebugDX11)

#	#DebugOpenGL flags
#	set(CMAKE_CXX_FLAGS_DEBUGOPENGL "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
#	set(CMAKE_C_FLAGS_DEBUGOPENGL "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
#	set(CMAKE_EXE_LINKER_FLAGS_DEBUGOPENGL "/debug /INCREMENTAL" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
#	set(CMAKE_SHARED_LINKER_FLAGS_DEBUGOPENGL "/debug /INCREMENTAL" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )

#	#ReleaseOpenGL flags
#	set(CMAKE_CXX_FLAGS_RELEASEOPENGL "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
#	set(CMAKE_C_FLAGS_RELEASEOPENGL "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
#	set(CMAKE_EXE_LINKER_FLAGS_RELEASEOPENGL "/INCREMENTAL:NO" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
#	set(CMAKE_SHARED_LINKER_FLAGS_RELEASEOPENGL "/INCREMENTAL:NO" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )
	
#	#DebugDX11 flags
#	set(CMAKE_CXX_FLAGS_DEBUGDX11 "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
#	set(CMAKE_C_FLAGS_DEBUGDX11 "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
#	set(CMAKE_EXE_LINKER_FLAGS_DEBUGDX11 "/debug /INCREMENTAL" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
#	set(CMAKE_SHARED_LINKER_FLAGS_DEBUGDX11 "/debug /INCREMENTAL" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )
	
#	#ReleaseDX11 flags
#	set(CMAKE_CXX_FLAGS_RELEASEDX11 "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
#	set(CMAKE_C_FLAGS_RELEASEDX11 "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
#	set(CMAKE_EXE_LINKER_FLAGS_RELEASEDX11 "/INCREMENTAL:NO" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
#	set(CMAKE_SHARED_LINKER_FLAGS_RELEASEDX11 "/INCREMENTAL:NO" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )

#  	set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
#    	$<$<CONFIG:DebugOpenGL>:TE_OPENGL>
#    	$<$<CONFIG:ReleaseOpenGL>:TE_OPENGL>
#    	$<$<CONFIG:DebugDirectX>:TE_DIRECTX>
#    	$<$<CONFIG:ReleaseDirectX>:TE_DIRECTX>
#  	)

##	set_directory_properties(PROPERTIES
##		COMPILE_DEFINITIONS_DEBUGOPENGL TE_OPENGL
##		COMPILE_DEFINITIONS_RELEASEOPENGL TE_OPENGL
##		COMPILE_DEFINITIONS_DEBUGDX11 TE_DX11
##		COMPILE_DEFINITIONS_RELEASEDX11 TE_DX11)
#endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Utils/CMake)

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
    set(CMAKE_CXX_COMPILER "clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -std=c++20 -stdlib=libc++ -ferror-limit=0")
    add_compile_defentions(-DTE_LINUX -DTE_OPENGL)
endif()

add_subdirectory(Code)
