add_executable(FightSpace)

set(HEADERS
    main.h)
set(SOURCES
    main.cpp)

target_sources(FightSpace PUBLIC ${HEADERS} PRIVATE ${SOURCES})

target_sourcegroup_init()
target_sourcegroup_add()
target_sourcegroup_done()

target_link_libraries(FightSpace 
    PRIVATE
        TECore
        TEngine
        TEPhysics
        TEPlatform
        TEGraphicsSystem
        TETransformSystem
        TENetworkSystem
        TEGameSystem)
#        CONAN_PKG::libpng
#        CONAN_PKG::luajit
#        CONAN_PKG::glew)

if(MSVC)
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG
        "${TEngine_SOURCE_DIR}/Executables")
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE
        "${TEngine_SOURCE_DIR}/Executables")
else()
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        "${TEngine_SOURCE_DIR}/Executables")
endif()

set_target_properties(FightSpace PROPERTIES FOLDER "4. Applications")
