add_library(TEGraphicsSystem "")

set(HEADERS
        TEGraphicsScene.h
        TEGraphicsSystem.h
        TEGraphicsObject.h
        TEGraphicsTask.h
        TERenderableObject.h
        TECameraObject.h)
set(SOURCES
        TEGraphicsScene.cpp
        TEGraphicsSystem.cpp
        TEGraphicsObject.cpp
        TEGraphicsTask.cpp
        TERenderableObject.cpp
        TECameraObject.cpp)

target_sources(TEGraphicsSystem PUBLIC ${HEADERS} PRIVATE ${SOURCES})

tengine_sourcegroup_init()
tengine_sourcegroup_add()
tengine_sourcegroup_done()

target_include_directories(TEGraphicsSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEGraphicsSystem PUBLIC TERendering PRIVATE TEngine)

set_target_properties(TEGraphicsSystem PROPERTIES FOLDER "2. TEngine Systems")
