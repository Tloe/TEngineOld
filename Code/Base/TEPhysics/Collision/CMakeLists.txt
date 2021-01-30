set(HEADERS
        TEBoundingVolumeCommon.h
        TEBVH.h
        TECollisionComponent.h
        TEContactGenerator.h
        TEPotentialContact.h)
set(SOURCES
        TEBVH.cpp
        TECollisionComponent.cpp
        TEContactGenerator.cpp)
target_sources(TEPhysics PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()