set(HEADERS
    TEVariant.h
    TECircularQue.h
    TEValue.h
    TEColor.h
    TETypeid.h
    TEDataTypes.h
    TETimer.h
    TETime.h
    TERandomNumberGenerators.h)
set(SOURCES
    TEVariant.cpp
    TEValue.cpp
    TEDataTypes.cpp
    TETimer.cpp
    TETime.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()
