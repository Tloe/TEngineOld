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

target_sourcegroup_init()
target_sourcegroup_add()
target_sourcegroup_done()


target_include_directories(TEGameSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEGameSystem PRIVATE TEngine)

if(MSVC)
        set_target_properties(TEGameSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
