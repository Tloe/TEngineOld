set(HEADERS
    TEInputContext.h
    TEInputMapper.h
    TEActionExecutor.h
    TEStateExecutor.h
    TERangeExecutor.h
    TEAction.h
    TEState.h
    TERange.h
    TEInput.h)
set(SOURCES
    TEInputContext.cpp
    TEInputMapper.cpp
    TEActionExecutor.cpp
    TEStateExecutor.cpp
    TERangeExecutor.cpp
    TERange.cpp
    TEInput.cpp)

target_sources(TEPlatform PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()