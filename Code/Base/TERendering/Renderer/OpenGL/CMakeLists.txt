set(HEADERS
    TERendererOpenGL.h    
    TEOpenGL.h
    TEVertexBufferOpenGL.h
    TEIndexBufferOpenGL.h
    TEVertexBufferLayoutOpenGL.h
    TEMappingOpenGL.h
    TETexture2DOpenGL.h)

set(SOURCES
    TERendererOpenGL.cpp
    TEMappingOpenGL.cpp
    TEVertexBufferOpenGL.cpp
    TEIndexBufferOpenGL.cpp
    TETexture2DOpenGL.cpp
    TEVertexBufferLayoutOpenGL.cpp)

target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

if(API_DIRECTX)
    set_source_files_properties(${SOURCES}
                                DIRECTORY ${TARGET_ROOT}
                                PROPERTIES HEADER_FILE_ONLY true)
endif()

target_sourcegroup_add()