target_sources(TEngine
    PUBLIC
        TESubject.h
        TEObserver.h
        TEChangeMasks.h
        TEChangeSyncer.h
        TEChangeData.h
    PRIVATE
        TESubject.cpp
        TEChangeSyncer.cpp
)

