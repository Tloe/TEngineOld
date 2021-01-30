set(HEADERS
        TESubject.h
        TEObserver.h
        TEChangeMasks.h
        TEChangeSyncer.h
        TEChangeData.h)
set(SOURCES
    TESubject.cpp
    TEChangeSyncer.cpp)

target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()