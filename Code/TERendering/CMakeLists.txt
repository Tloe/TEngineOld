#TERendering

#TERendering/Renderer
set(renderer_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TERenderer.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TEShaderParameter.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TEApiRendererIncludes.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TEApiResourcesIncludes.h)
source_group(Renderer FILES ${renderer_headers})

set(renderer_source
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TERenderer.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/TEShaderParameter.cpp)
source_group(Renderer FILES ${renderer_source})

set(renderer_dx11_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEVertexBufferDX11.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEIndexBufferDX11.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEVertexBufferLayoutDX11.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEMappingDX11.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TERendererDX11.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TETexture2DDX11.h)
source_group(Renderer\\DX11 FILES ${renderer_dx11_headers})

set(renderer_dx11_source
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEVertexBufferDX11.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEIndexBufferDX11.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TERendererDX11.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEMappingDX11.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TEVertexBufferLayoutDX11.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/TETexture2DDX11.cpp)
source_group(Renderer\\DX11 FILES ${renderer_dx11_source})

set(renderer_opengl_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEVertexBufferOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEIndexBufferOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEVertexBufferLayoutOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEMappingOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TERendererOpenGL.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TETexture2DOpenGL.h)
source_group(Renderer\\OpenGL FILES ${renderer_opengl_headers})

set(renderer_opengl_source
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TERendererOpenGL.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEMappingOpenGL.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEVertexBufferOpenGL.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEIndexBufferOpenGL.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TETexture2DOpenGL.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/TEVertexBufferLayoutOpenGL.cpp)
source_group(Renderer\\OpenGL FILES ${renderer_opengl_source})

#TERendering/Resources
set(resources_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TEMesh.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TEMeshStructs.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TETexture.h
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TEEffect.h)
source_group(Renderer\\CommonResources FILES ${resources_headers})

set(resources_source
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TEMesh.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TETexture.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/CommonResources/TEEffect.cpp)
source_group(Renderer\\CommonResources FILES ${resources_source})

#TERendering/SceneGraph
set(scenegraph_headers
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TESceneManager.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEAlphaBlending.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TECamera.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TECameraNode.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TECullState.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEFogState.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEGlobalState.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TELight.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TELightNode.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEMaterialState.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TENode.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TERenderable.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TESpatial.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEWireframe.h
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEZBufferState.h)
source_group(SceneGraph FILES ${scenegraph_headers})

set(scenegraph_source
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TESceneManager.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TECamera.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TECameraNode.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TEGlobalState.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TELight.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TELightNode.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TENode.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TERenderable.cpp
${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/TESpatial.cpp)
source_group(SceneGraph FILES ${scenegraph_source})


set(context_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEApiContextIncludes.h)
source_group(Context FILES ${context_headers})

set(context_linux_opengl_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextLinuxOpenGL.h)
source_group(Context\\Linux FILES ${context_linux_opengl_headers})

set(context_win_dx11_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextWinDX11.h)
source_group(Context\\Windows\\DX11 FILES ${context_win_dx11_headers})

set(context_win_opengl_headers
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextWinOpenGL.h)
source_group(Context\\Windows\\OpenGL FILES ${context_win_opengl_headers})

set(context_win_opengl_source
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextWinOpenGL.cpp)
source_group(Context\\Windows\\OpenGL FILES ${context_win_opengl_source})

set(context_linux_opengl_source
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextLinuxOpenGL.cpp)
source_group(Context\\Linux FILES ${context_linux_opengl_source})

set(context_win_dx11_source
${TEngine_SOURCE_DIR}/Code/TERendering/Context/TEContextWinDX11.cpp)
source_group(Context\\Windows\\DX11 FILES ${context_win_dx11_source})

include_directories(
${terendering_dirs}
${tecore_dirs}
${tengine_dirs}
${teplatform_dirs}
${CG_INCLUDE_PATH}
${external_glew_include}
${TEngine_SOURCE_DIR}/Externals/OpenGL)

if(MSVC)
	set(Exclude_MSVC_Linux
		${context_linux_opengl_source}
		${context_linux_opengl_headers})
	set(Exclude_MSVC_DX11
		${renderer_dx11_headers}
		${renderer_dx11_source}
		${context_win_dx11_headers}
		${context_win_dx11_source})
	set(Exclude_MSVC_OpenGL
		${renderer_opengl_headers}
		${renderer_opengl_source}
		${context_win_opengl_headers}
		${context_win_opengl_source})

       set(filecontent "ALL ${Exclude_MSVC_Linux} DebugOpenGL ${Exclude_MSVC_DX11} ReleaseOpenGL ${Exclude_MSVC_DX11} DebugDX11 ${Exclude_MSVC_OpenGL} ReleaseDX11 ${Exclude_MSVC_OpenGL} ")
	string(REPLACE ";" " " filecontent "${filecontent}")
	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/" "" filecontent "${filecontent}")
	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/" "" filecontent "${filecontent}")
	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/" "" filecontent "${filecontent}")
	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/" "" filecontent "${filecontent}")
	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Context/" "" filecontent "${filecontent}")
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/RendererExcludes.txt "${filecontent}")
	add_custom_target(ExcludeFilesFromTERendering ALL
    COMMAND ${TEngine_SOURCE_DIR}/Utils/CMake/ExcludeFilesFromProject.exe ${CMAKE_CURRENT_BINARY_DIR}/TERendering.vcxproj ${CMAKE_CURRENT_BINARY_DIR}/RendererExcludes.txt)
endif()
if(UNIX)
	set_source_files_properties(
		${context_win_opengl_headers}
		${context_win_opengl_source}
		${context_win_dx11_headers}
		${context_win_dx11_source}
		${renderer_dx11_headers}
		${renderer_dx11_source}
		PROPERTIES HEADER_FILE_ONLY true)

	find_package(X11 REQUIRED)
	include_directories(${X11_INCLUDE_DIR})
	#link_directories(${X11_LIBRARIES} ${CG_LIBARARY_PATH})
endif()

#OpenGL
find_package(OpenGL REQUIRED)

add_library(TERendering
	${engine_headers}
	${engine_source}
	${renderer_headers}
	${renderer_source}	
	${renderer_dx11_headers}
	${renderer_dx11_source}
	${renderer_opengl_headers}
	${renderer_opengl_source}
	${resources_headers}
	${resources_source}
	${scenegraph_headers}
	${scenegraph_source}
    ${context_headers}
	${context_linux_opengl_headers}
	${context_win_dx11_headers}
	${context_win_opengl_headers}
	${context_win_opengl_source}
	${context_linux_opengl_source}
	${context_win_dx11_source})

if(WIN32)
	target_link_libraries(
		TERendering
		TECore
		TEPlatform
		${glew_libraries}
		${OPENGL_LIBRARIES}
		${cg_libs})
elseif(UNIX)
	target_link_libraries(
		TERendering
		TECore
		TEPlatform
                ${glew_libraries}
		${cg_libs}
		${OPENGL_LIBRARIES})
endif()

if(MSVC)
	add_dependencies(TERendering ExcludeFilesFromTERendering)
	set_target_properties(TERendering PROPERTIES FOLDER "0. TELibs")
	set_target_properties(ExcludeFilesFromTERendering PROPERTIES FOLDER "9. CMake")
endif()
