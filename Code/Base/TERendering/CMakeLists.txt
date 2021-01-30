add_library(TERendering)

target_sourcegroup_init()

add_subdirectory(Context)
add_subdirectory(Renderer)
add_subdirectory(SceneGraph)

target_sourcegroup_done()

target_link_libraries(TERendering
    PUBLIC
        TEPlatform
    PRIVATE
        TECore
        CONAN_PKG::glew
        CONAN_PKG::opengl)

 target_include_directories(TERendering
    PUBLIC
        Context
        Renderer
        Renderer/CommonResources
        Renderer/DX11
        Renderer/OpenGL
        SceneGraph)

if(MSVC)
	set_target_properties(TERendering PROPERTIES FOLDER "0. TELibs")
endif()
