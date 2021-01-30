add_library(TENetworkSystem "")

set(HEADERS
        TENetworkSystem.h
        TENetworkScene.h
        TENetworkObject.h
        TENetworkTask.h
        TENetworkManager.h
        TEOutgoing.h
        TEMessageHandler.h)
set(SOURCES
        TENetworkSystem.cpp
        TENetworkScene.cpp
        TENetworkObject.cpp
        TENetworkTask.cpp
        TENetworkManager.cpp
        TEMessageHandler.cpp)

target_sources(TENetworkSystem PUBLIC ${HEADERS} PRIVATE ${SOURCES})

target_sourcegroup_init()
target_sourcegroup_add()
target_sourcegroup_done()

target_include_directories(TENetworkSystem
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(TENetworkSystem PRIVATE TEngine)

if(MSVC)
    set_target_properties(TENetworkSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
