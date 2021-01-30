set(HEADERS
    TEVertexBufferDX11.h
    TEIndexBufferDX11.h
    TEVertexBufferLayoutDX11.h
    TEMappingDX11.h
    TERendererDX11.h
    TETexture2DDX11.h)

set(SOURCES
    TEVertexBufferDX11.cpp
    TEIndexBufferDX11.cpp
    TERendererDX11.cpp
    TEMappingDX11.cpp
    TEVertexBufferLayoutDX11.cpp
    TETexture2DDX11.cpp)


target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

if(API_OPENGL)
    set_source_files_properties(${SOURCES}
                                DIRECTORY ${TARGET_ROOT}
                                PROPERTIES HEADER_FILE_ONLY true)
endif()

target_sourcegroup_add()