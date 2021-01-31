set(HEADERS
    TEMesh.h
    TEMeshStructs.h
    TETexture.h
    TEEffect.h)

set(SOURCES
    TEMesh.cpp
    TETexture.cpp
    TEEffect.cpp)

target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()
