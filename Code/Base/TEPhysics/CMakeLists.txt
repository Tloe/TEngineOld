add_library(TEPhysics "")

add_subdirectory(Collision)
add_subdirectory(Physics)

target_link_libraries(TEPhysics PUBLIC TECore)

target_include_directories(TEPhysics
    PUBLIC
        Collision
        Physics
)

if(MSVC)
	set_target_properties(TEPhysics PROPERTIES FOLDER "0. TELibs")
endif()
