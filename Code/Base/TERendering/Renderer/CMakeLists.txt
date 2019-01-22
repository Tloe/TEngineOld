target_sources(TERendering
    PUBLIC
        TERenderer.h
        TEShaderParameter.h
        TEApiRendererIncludes.h
        TEApiResourcesIncludes.h
    PRIVATE
        TERenderer.cpp
        TEShaderParameter.cpp
)

add_subdirectory(CommonResources)
add_subdirectory(OpenGL)
if(WIN32)
    add_subdirectory(DX11)
endif()

