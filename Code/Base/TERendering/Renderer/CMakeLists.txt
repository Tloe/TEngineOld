set(HEADERS
    TERenderer.h
    TEShaderParameter.h
    TEApiRendererIncludes.h
    TEApiResourcesIncludes.h)
set(SOURCES
    TERenderer.cpp
    TEShaderParameter.cpp)
target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

add_subdirectory(CommonResources)
add_subdirectory(OpenGL)

if(WIN32)
    add_subdirectory(DX11)
endif()

target_sourcegroup_add()
