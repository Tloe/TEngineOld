add_library(TERendering "")

# if(MSVC)
# 	set(Exclude_MSVC_Linux
# 		${context_linux_opengl_source}
# 		${context_linux_opengl_headers})
# 	set(Exclude_MSVC_DX11
# 		${renderer_dx11_headers}
# 		${renderer_dx11_source}
# 		${context_win_dx11_headers}
# 		${context_win_dx11_source})
# 	set(Exclude_MSVC_OpenGL
# 		${renderer_opengl_headers}
# 		${renderer_opengl_source}
# 		${context_win_opengl_headers}
# 		${context_win_opengl_source})

#        set(filecontent "ALL ${Exclude_MSVC_Linux} DebugOpenGL ${Exclude_MSVC_DX11} ReleaseOpenGL ${Exclude_MSVC_DX11} DebugDX11 ${Exclude_MSVC_OpenGL} ReleaseDX11 ${Exclude_MSVC_OpenGL} ")
# 	string(REPLACE ";" " " filecontent "${filecontent}")
# 	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/DX11/" "" filecontent "${filecontent}")
# 	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/OpenGL/" "" filecontent "${filecontent}")
# 	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Renderer/" "" filecontent "${filecontent}")
# 	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/SceneGraph/" "" filecontent "${filecontent}")
# 	string(REPLACE "${TEngine_SOURCE_DIR}/Code/TERendering/Context/" "" filecontent "${filecontent}")
# 	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/RendererExcludes.txt "${filecontent}")
# 	add_custom_target(ExcludeFilesFromTERendering ALL
#     COMMAND ${TEngine_SOURCE_DIR}/Utils/CMake/ExcludeFilesFromProject.exe ${CMAKE_CURRENT_BINARY_DIR}/TERendering.vcxproj ${CMAKE_CURRENT_BINARY_DIR}/RendererExcludes.txt)
# endif()


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(Context)
add_subdirectory(Renderer)
add_subdirectory(SceneGraph)

target_include_directories(TERendering
    PUBLIC
        Context
        Renderer
        Renderer/CommonResources
        Renderer/DX11
        Renderer/OpenGL
        SceneGraph
    PRIVATE
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INLCUDE_DIR}
)

target_link_libraries(TERendering
    PUBLIC
        TECore
        TEPlatform
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
)

if(MSVC)
	# add_dependencies(TERendering ExcludeFilesFromTERendering)
	set_target_properties(TERendering PROPERTIES FOLDER "0. TELibs")
	# set_target_properties(ExcludeFilesFromTERendering PROPERTIES FOLDER "9. CMake")
endif()
