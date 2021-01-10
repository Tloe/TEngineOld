#function(add_source_by_config_regex _target _encapsulation _regex)
#    foreach(_config IN LISTS CMAKE_CONFIGURATION_TYPES CMAKE_BUILD_TYPE)
#        if (_config MATCHES "${_regex}")
#            target_sources(${_target} ${_encapsulation} $<$<CONFIG:${_config}>:${ARGN}>)
#        endif()
#    endforeach()
#endfunction()

if(UNIX OR Config_API STREQUAL "OpenGL")
    target_sources(TERendering
        PUBLIC
            TEOpenGL.h
            TEVertexBufferOpenGL.h
            TEIndexBufferOpenGL.h
            TEVertexBufferLayoutOpenGL.h
            TEMappingOpenGL.h
            TERendererOpenGL.h
            TETexture2DOpenGL.h
        PRIVATE
            TERendererOpenGL.cpp
            TEMappingOpenGL.cpp
            TEVertexBufferOpenGL.cpp
            TEIndexBufferOpenGL.cpp
            TETexture2DOpenGL.cpp
            TEVertexBufferLayoutOpenGL.cpp
    )
    message("OpenGL files added!")
endif()

