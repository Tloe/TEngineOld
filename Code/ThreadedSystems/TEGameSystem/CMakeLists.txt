add_library(TEGameSystem "")

target_sources(TEGameSystem
    PUBLIC
        TEGameSystem.h
        TEGameScene.h
        TEGameTask.h
        TEActorObject.h
        TESpawnerObject.h
    PRIVATE
        TEGameSystem.cpp
        TEGameScene.cpp
        TEGameTask.cpp
        TEActorObject.cpp
        TESpawnerObject.cpp)

target_include_directories(TEGameSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TEGameSystem PUBLIC TEngine)

if(MSVC)
        set_target_properties(TEGameSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
