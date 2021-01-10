target_sources(TERendering PUBLIC TEApiContextIncludes.h)

if(UNIX)
    target_sources(TERendering
        PUBLIC
            TEContextLinuxOpenGL.h
        PRIVATE
            TEContextLinuxOpenGL.cpp)
elseif(WIN32)
    if(Config_API STREQUAL "OpenGL")
        target_sources(TERendering
        PUBLIC
            TEContextWinOpenGL.h
        PRIVATE
            TEContextWinOpenGL.cpp)
    elseif(Config_API STREQUAL "DirectX")
        target_sources(TERendering
        PUBLIC
            TEContextWinDX11.h
        PRIVATE
            TEContextWinDX11.cpp)
    endif()
endif()

