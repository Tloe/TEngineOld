add_library(TEPhysicsSystem "")

target_sources(TEPhysicsSystem
    PUBLIC
        TEPhysicsObject.h
    PRIVATE
        TEPhysicsObject.cpp)

target_include_directories(TEPhysicsSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEPhysicsSystem PUBLIC TEngine)

if(MSVC)
	set_target_properties(TEPhysicsSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
