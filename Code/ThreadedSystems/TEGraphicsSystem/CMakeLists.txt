add_library(TEGraphicsSystem "")

target_sources(TEGraphicsSystem
    PUBLIC
        TEGraphicsScene.h
        TEGraphicsSystem.h
        TEGraphicsObject.h
        TEGraphicsTask.h
        TERenderableObject.h
        TECameraObject.h
    PRIVATE
        TEGraphicsScene.cpp
        TEGraphicsSystem.cpp
        TEGraphicsObject.cpp
        TEGraphicsTask.cpp
        TERenderableObject.cpp
        TECameraObject.cpp)

target_include_directories(TEGraphicsSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEGraphicsSystem PUBLIC TEngine TERendering)

if(MSVC)
	set_target_properties(TEGraphicsSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
