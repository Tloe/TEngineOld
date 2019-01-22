add_library(TENetworkSystem "")

target_sources(TENetworkSystem
    PUBLIC
        TENetworkSystem.h
        TENetworkScene.h
        TENetworkObject.h
        TENetworkTask.h
        TENetworkManager.h
        TEOutgoing.h
        TEMessageHandler.h
    PRIVATE
        TENetworkSystem.cpp
        TENetworkScene.cpp
        TENetworkObject.cpp
        TENetworkTask.cpp
        TENetworkManager.cpp
        TEMessageHandler.cpp)

target_include_directories(TENetworkSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TENetworkSystem PUBLIC TEngine)

if(MSVC)
    set_target_properties(TENetworkSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
