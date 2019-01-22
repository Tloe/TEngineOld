target_sources(TEPhysics
    PUBLIC
        TEBoundingVolumeCommon.h
        TEBVH.h
        TECollisionComponent.h
        TEContactGenerator.h
        TEPotentialContact.h
    PRIVATE
        TEBVH.cpp
        TECollisionComponent.cpp
        TEContactGenerator.cpp
)

