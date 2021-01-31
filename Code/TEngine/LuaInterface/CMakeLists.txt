set(HEADERS
    TELuaInterface.h)
set(SOURCES
    TELuaInterface.cpp)

target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()