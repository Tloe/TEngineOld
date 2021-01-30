set(HEADERS
    TESystemTask.h
    TESystem.h
    TESystemScene.h
    TESystemObject.h)
set(SOURCES
    TESystemTask.cpp
    TESystemObject.cpp
    TESystem.cpp
    TESystemScene.cpp)

target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()
