set(HEADERS
        TEPhysicsComponent.h)
set(SOURCES
        TEPhysicsComponent.cpp)

target_sources(TEPhysics PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()