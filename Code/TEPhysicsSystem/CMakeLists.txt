#TEPhysicsSystem

set(physicssystem_headers
${TEngine_SOURCE_DIR}/Code/TEPhysicsSystem/TEPhysicsObject.h
)

set(physicssystem_source
${TEngine_SOURCE_DIR}/Code/TEPhysicsSystem/TEPhysicsObject.cpp
)

include_directories(
${tephysicssystem_dirs}
${external_luajit_include}
)

add_library(TEPhysicsSystem
${physicssystem_headers}
${physicssystem_source})

target_link_libraries(TEPhysicsSystem TEngine)

if(MSVC)
	set_target_properties(TEPhysicsSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()