add_subdirectory(Events)

target_sources(TEngine
    PUBLIC
        TEEventManager.h
        TEEventHandler.h
        TEQuedEvent.h
    PRIVATE
        TEEventManager.cpp
        TEEventHandler.cpp
)
