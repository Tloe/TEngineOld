#TEGuiSystem

set(gamesystem_headers
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameSystem.h
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameScene.h
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameTask.h
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEActorObject.h
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TESpawnerObject.h)

set(gamesystem_source
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameSystem.cpp
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameScene.cpp
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEGameTask.cpp
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TEActorObject.cpp
${TEngine_SOURCE_DIR}/Code/TEGameSystem/TESpawnerObject.cpp)

include_directories(
${tegamesystem_dirs}
${tecore_dirs}
${tengine_dirs}
${external_jsoncpp_include}
${external_luajit_include})

add_library(TEGameSystem
${gamesystem_headers}
${gamesystem_source})

target_link_libraries(TEGameSystem TEngine)

if(MSVC)
        set_target_properties(TEGameSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
