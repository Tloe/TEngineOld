set(HEADERS
    TESceneManager.h
    TEAlphaBlending.h
    TECamera.h
    TECameraNode.h
    TECullState.h
    TEFogState.h
    TEGlobalState.h
    TELight.h
    TELightNode.h
    TEMaterialState.h
    TENode.h
    TERenderable.h
    TESpatial.h
    TEWireframe.h
    TEZBufferState.h)
set(SOURCES
    TESceneManager.cpp
    TECamera.cpp
    TECameraNode.cpp
    TEGlobalState.cpp
    TELight.cpp
    TELightNode.cpp
    TENode.cpp
    TERenderable.cpp
    TESpatial.cpp)

target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()