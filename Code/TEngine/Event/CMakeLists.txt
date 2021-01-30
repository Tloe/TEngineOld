set(HEADERS
    TEEventManager.h
    TEEventHandler.h
    TEQuedEvent.h)
set(SOURCES
    TEEventManager.cpp
    TEEventHandler.cpp)
target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

add_subdirectory(Events)

target_sourcegroup_add()