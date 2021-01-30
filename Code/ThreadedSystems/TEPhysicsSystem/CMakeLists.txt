add_library(TEPhysicsSystem "")

set(HEADERS
    TEPhysicsObject.h)
set(SOURCES
    TEPhysicsObject.cpp)

target_sources(TEPhysicsSystem PUBLIC ${HEADERS} PRIVATE ${SOURCES})

target_sourcegroup_init()
target_sourcegroup_add()
target_sourcegroup_done()

target_include_directories(TEPhysicsSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEPhysicsSystem PRIVATE TEngine)

set_target_properties(TEPhysicsSystem PROPERTIES FOLDER "2. TEngine Systems")
