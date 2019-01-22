add_library(TETransformSystem "")

target_sources(TETransformSystem
    PUBLIC
        TETransformSystem.h
        TETransformObject.h
        TETransformScene.h
    PRIVATE
        TETransformSystem.cpp
        TETransformObject.cpp
        TETransformScene.cpp)


target_include_directories(TETransformSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TETransformSystem PUBLIC TEngine)

if(MSVC)
	set_target_properties(TETransformSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
