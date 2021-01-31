set(HEADERS
    TEEventVisitor.h
    TEResolutionEvent.h
    TEAddForceEvent.h
    TETranslationEvent.h
    TEScaleEvent.h
    TEOrientationEvent.h
    TEEnvironmentUpdateEvent.h)
set(SOURCES
    TEEventVisitor.cpp
    TEResolutionEvent.cpp
    TEAddForceEvent.cpp
    TETranslationEvent.cpp
    TEScaleEvent.cpp
    TEOrientationEvent.cpp
    TEEnvironmentUpdateEvent.cpp)
target_sources(TEngine PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()