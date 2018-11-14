#TENetworkSystem

set(networksystem_headers
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkSystem.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkScene.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkObject.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkTask.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkManager.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TEOutgoing.h
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TEMessageHandler.h)

set(networksystem_source
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkSystem.cpp
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkScene.cpp
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkObject.cpp
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkTask.cpp
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TENetworkManager.cpp
${TEngine_SOURCE_DIR}/Code/TENetworkSystem/TEMessageHandler.cpp)

include_directories(
${tenetworksystem_dirs}
${tecore_dirs}
${tengine_dirs}
${external_jsoncpp_include}
${external_luajit_include})

add_library(TENetworkSystem
${networksystem_headers}
${networksystem_source})

target_link_libraries(TENetworkSystem TEngine)

if(MSVC)
    set_target_properties(TENetworkSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
