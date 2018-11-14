#TEngine

cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0043 NEW)

project(TEngine)

set(tecore_dirs
${TEngine_SOURCE_DIR}/Code/TECore/Events/
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/
${TEngine_SOURCE_DIR}/Code/TECore/Math/
${TEngine_SOURCE_DIR}/Code/TECore/Network/
${TEngine_SOURCE_DIR}/Code/TECore/Resources/
${TEngine_SOURCE_DIR}/Code/TECore/IO/
${TEngine_SOURCE_DIR}/Code/TECore/Images/
${TEngine_SOURCE_DIR}/Code/TECore/Lua/
${TEngine_SOURCE_DIR}/Code/TECore/Utils/
${TEngine_SOURCE_DIR}/Code/TECore/Threading/)

set(terendering_dirs
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer
${TEngine_SOURCE_DIR}/Code/TERendering/Resources
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph
${TEngine_SOURCE_DIR}/Code/TERendering/Context)

set(tephysics_dirs
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision
${TEngine_SOURCE_DIR}/Code/TEPhysics/Physics)

set(tengine_dirs
${TEngine_SOURCE_DIR}/Code/TEngine/Engine
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems
${TEngine_SOURCE_DIR}/Code/TEngine/Event
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events
${TEngine_SOURCE_DIR}/Code/TEngine/LuaInterface)

set(tetransformsystem_dirs
${TEngine_SOURCE_DIR}/Code/TETransformSystem
)

set(tegraphicssystem_dirs
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem
)

set(tephysicssystem_dirs
${TEngine_SOURCE_DIR}/Code/TEPhysicsSystem
)

set(tegamesystem_dirs
${TEngine_SOURCE_DIR}/Code/TEGameSystem)

set(teplatform_dirs
${TEngine_SOURCE_DIR}/Code/TEPlatform
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping
${TEngine_SOURCE_DIR}/Code/TEPlatform/Win
${TEngine_SOURCE_DIR}/Code/TEPlatform/Linux
)

set(tenetworksystem_dirs
${TEngine_SOURCE_DIR}/Code/TENetworkSystem)


set(EXECUTABLE_OUTPUT_PATH "${TEngine_SOURCE_DIR}/Executables")

if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "9. CMake")
		
	set(CMAKE_CONFIGURATION_TYPES "DebugOpenGL;ReleaseOpenGL;DebugDX11;ReleaseDX11")
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
		"Reset the configurations to what we need"
		FORCE)
	set_property(GLOBAL PROPERTY DEBUG_CONFIGURATIONS DebugOpenGL DebugDX11)

	#DebugOpenGL flags
	set(CMAKE_CXX_FLAGS_DEBUGOPENGL "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
	set(CMAKE_C_FLAGS_DEBUGOPENGL "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
	set(CMAKE_EXE_LINKER_FLAGS_DEBUGOPENGL "/debug /INCREMENTAL" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUGOPENGL "/debug /INCREMENTAL" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )

	#ReleaseOpenGL flags
	set(CMAKE_CXX_FLAGS_RELEASEOPENGL "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
	set(CMAKE_C_FLAGS_RELEASEOPENGL "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASEOPENGL "/INCREMENTAL:NO" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASEOPENGL "/INCREMENTAL:NO" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )
	
	#DebugDX11 flags
	set(CMAKE_CXX_FLAGS_DEBUGDX11 "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
	set(CMAKE_C_FLAGS_DEBUGDX11 "/D_DEBUG /MDd /Zi  /Ob0 /Od /RTC1" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
	set(CMAKE_EXE_LINKER_FLAGS_DEBUGDX11 "/debug /INCREMENTAL" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUGDX11 "/debug /INCREMENTAL" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )
	
	#ReleaseDX11 flags
	set(CMAKE_CXX_FLAGS_RELEASEDX11 "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C++ compiler during maintainer builds." FORCE)
	set(CMAKE_C_FLAGS_RELEASEDX11 "/MD /O2 /Ob2 /D NDEBUG" CACHE STRING "Flags used by the C compiler during maintainer builds." FORCE)
	set(CMAKE_EXE_LINKER_FLAGS_RELEASEDX11 "/INCREMENTAL:NO" CACHE STRING "Flags used for linking binaries during maintainer builds." FORCE )
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASEDX11 "/INCREMENTAL:NO" CACHE STRING "Flags used by the shared libraries linker during maintainer builds." FORCE )

  	set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    	$<$<CONFIG:DebugOpenGL>:TE_OPENGL>
    	$<$<CONFIG:ReleaseOpenGL>:TE_OPENGL>
    	$<$<CONFIG:DebugDirectX>:TE_DIRECTX>
    	$<$<CONFIG:ReleaseDirectX>:TE_DIRECTX>
  	)

#	set_directory_properties(PROPERTIES
#		COMPILE_DEFINITIONS_DEBUGOPENGL TE_OPENGL
#		COMPILE_DEFINITIONS_RELEASEOPENGL TE_OPENGL
#		COMPILE_DEFINITIONS_DEBUGDX11 TE_DX11
#		COMPILE_DEFINITIONS_RELEASEDX11 TE_DX11)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Utils/CMake)

set(ENET_INCLUDE ${TEngine_SOURCE_DIR}/Externals/enet-1.3.0/include)
set(external_assimp_include ${TEngine_SOURCE_DIR}/Externals/assimp--3.0.1270-sdk/include)
set(LIBPNG_INCLUDE ${TEngine_SOURCE_DIR}/Externals/libpng-1.5.9)
set(external_glew_include ${TEngine_SOURCE_DIR}/Externals/glew-1.9.0/include)
set(external_luajit_include ${TEngine_SOURCE_DIR}/Externals/LuaJIT-2.0.4/src)

set(winsock2_lib "ws2_32.lib")
if(WIN32)
    set(v8_lib_R ${TEngine_SOURCE_DIR}/Externals/v8/build/Release/lib/v8_snapshot.lib)
    set(external_luajit_lib ${TEngine_SOURCE_DIR}/Externals/LuaJIT-2.0.4/src/lua51.lib)
endif()

FIND_PACKAGE(Cg REQUIRED)
if(CG_FOUND)
    if(WIN32)
        set(cg_libs ${CG_LIBRARY} ${CG_GL_LIBRARY} ${CG_D3D11_LIBRARY})
    elseif(UNIX)
        set(cg_libs ${CG_LIBRARY} ${CG_GL_LIBRARY})
    endif()
endif()

if(WIN32)
    set(libpng_lib ${TEngine_SOURCE_DIR}/Externals/libpng-1.5.9/projects/vstudio/Release/libpng15.lib)
    set(glew_libraries ${TEngine_SOURCE_DIR}/Externals/glew-1.9.0/lib/glew32.lib)
    set(external_assimp_lib_R ${TEngine_SOURCE_DIR}/Externals/assimp--3.0.1270-sdk/lib/assimp_release-st_win32/assimp.lib)
    set(external_assimp_lib_D ${TEngine_SOURCE_DIR}/Externals/assimp--3.0.1270-sdk/lib/assimp_debug-st_win32/assimp.lib)
    add_definitions(-D TE_WINDOWS)
    add_definitions(-D _WIN32_WINDOWS)
    add_definitions(-D WIN32_LEAN_AND_MEAN)
    add_definitions(-D _HAS_ITERATOR_DEBUGGING=0)
    add_definitions(-D _CRT_SECURE_NO_WARNINGS)
    add_definitions(-D NOMINMAX)
elseif(UNIX)
    set(libpng_lib ${TEngine_SOURCE_DIR}/Externals/libpng-1.5.9/build/libpng15.so)
    set(glew_libraries ${TEngine_SOURCE_DIR}/Externals/glew-1.9.0/lib/libGLEW.so)
    set(external_assimp_lib ${TEngine_SOURCE_DIR}/Externals/assimp--3.0.1270-sdk/build/code/libassimp.so)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
    add_definitions(-D TE_LINUX -DTE_OPENGL -std=c++0x)
endif()

subdirs(Code)
