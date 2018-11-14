#LibProject/src

set(collision_headers
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEBoundingVolumeCommon.h
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEBVH.h
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TECollisionComponent.h
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEContactGenerator.h
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEPotentialContact.h
)
source_group(Collision FILES ${collision_headers})

set(collision_source
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEBVH.cpp
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TECollisionComponent.cpp
${TEngine_SOURCE_DIR}/Code/TEPhysics/Collision/TEContactGenerator.cpp
)
source_group(Collision FILES ${collision_source})

set(physics_headers ${TEngine_SOURCE_DIR}/Code/TEPhysics/Physics/TEPhysicsComponent.h)
source_group(Physics FILES ${physics_headers})

set(physics_source
${TEngine_SOURCE_DIR}/Code/TEPhysics/Physics/TEPhysicsComponent.cpp)
source_group(Physics FILES ${physics_source})

include_directories(
${tephysics_dirs}
${tecore_dirs}
)

add_library(TEPhysics
${collision_headers}
${collision_source}
${physics_headers}
${physics_source})

target_link_libraries(TEPhysics TEngine TECore)

if(MSVC)
	set_target_properties(TEPhysics PROPERTIES FOLDER "0. TELibs")
endif()