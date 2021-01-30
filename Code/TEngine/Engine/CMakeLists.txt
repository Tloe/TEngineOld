set(HEADERS
    TEEngine.h
    TEUniversalScene.h
    TEUniversalObject.h
    TEScheduler.h
    TEEnvironment.h
    TESceneHandler.h)
set(SOURCES
    TEEngine.cpp
    TEUniversalScene.cpp
    TEUniversalObject.cpp
    TEScheduler.cpp
    TEEnvironment.cpp
    TESceneHandler.cpp)
target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

add_subdirectory(Change)
add_subdirectory(Systems)

target_sourcegroup_add()