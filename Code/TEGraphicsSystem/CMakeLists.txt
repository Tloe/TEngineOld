#TEGraphicsSystem

#TEGraphicsSystem/Engine
set(graphicssystem_headers
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsScene.h
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsSystem.h
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsObject.h
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsTask.h
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TERenderableObject.h
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TECameraObject.h)

set(graphicssystem_source
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsScene.cpp
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsSystem.cpp
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsObject.cpp
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TEGraphicsTask.cpp
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TERenderableObject.cpp
${TEngine_SOURCE_DIR}/Code/TEGraphicsSystem/TECameraObject.cpp)

include_directories(
${tegraphicssystem_dirs}
${tecore_dirs}
${teplatform_dirs}
${terendering_dirs}
${tengine_dirs}
${external_luajit_include}
${external_glew_include})

add_library(TEGraphicsSystem
	${graphicssystem_headers}
	${graphicssystem_source})

if(WIN32)
	target_link_libraries(
		TEGraphicsSystem
		TECore
		TEngine
		TERendering
		TEPlatform)
elseif(UNIX)
	find_package(X11 REQUIRED)
    include_directories(SYSTEM ${X11_INCLUDE_DIR})
	target_link_libraries(
		TEGraphicsSystem
		TECore
		TERendering)
endif()

if(MSVC)
	set_target_properties(TEGraphicsSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
