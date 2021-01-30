set(HEADERS 
    TEApiContextIncludes.h
    TEContextLinuxOpenGL.h
    TEContextWinOpenGL.h
    TEContextWinDX11.h)
set(SOURCES
    TEContextLinuxOpenGL.cpp
    TEContextWinOpenGL.cpp
    TEContextWinDX11.cpp)

target_sources(TERendering PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

if(UNIX)
    set_source_files_properties(TEContextWinOpenGL.cpp TEContextWinDX11.cpp
                                DIRECTORY ${TARGET_ROOT}
                                PROPERTIES HEADER_FILE_ONLY TRUE)    
elseif(WIN32)
    if(API_OPENGL)
        set_source_files_properties(TEContextLinuxOpenGL.cpp TEContextWinDX11.cpp
                                    DIRECTORY ${TARGET_ROOT}
                                    PROPERTIES HEADER_FILE_ONLY true)
    elseif(API_DIRECTX)
        message("WIN32-DIRECTX")
        set_source_files_properties(TEContextLinuxOpenGL.cpp TEContextWinDX11.cpp
                                    DIRECTORY ${TARGET_ROOT}
                                    PROPERTIES HEADER_FILE_ONLY true)
    endif()
endif()
    
target_sourcegroup_add()
