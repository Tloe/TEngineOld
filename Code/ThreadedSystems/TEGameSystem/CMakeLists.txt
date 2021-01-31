add_library(TEGameSystem "")

set(HEADERS
    TEGameSystem.h
    TEGameScene.h
    TEGameTask.h
    TEActorObject.h
    TESpawnerObject.h)
set(SOURCES
    TEGameSystem.cpp
    TEGameScene.cpp
    TEGameTask.cpp
    TEActorObject.cpp
    TESpawnerObject.cpp)

target_sources(TEGameSystem PUBLIC ${HEADERS} PRIVATE ${SOURCES})

tengine_sourcegroup_init()
tengine_sourcegroup_add()
tengine_sourcegroup_done()


target_include_directories(TEGameSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEGameSystem PRIVATE TEngine)

set_target_properties(TEGameSystem PROPERTIES FOLDER "2. TEngine Systems")
