set(HEADERS
    TELockQue.h
    TEThreadPool.h
    TEWorkStealingQue.h
    TEFunctionWrapper.h
    TEThreadJoiner.h
    TEFutureJoiner.h)
set(SOURCES
    TEThreadPool.cpp
    TEWorkStealingQue.cpp
    TEFunctionWrapper.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()