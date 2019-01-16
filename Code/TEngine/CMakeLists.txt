#TEngine/src

set(engine_headers
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEEngine.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEUniversalScene.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEUniversalObject.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEScheduler.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEEnvironment.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TESceneHandler.h)
source_group(Engine FILES ${engine_headers})

set(engine_source
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEEngine.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEUniversalScene.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEUniversalObject.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEScheduler.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TEEnvironment.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/TESceneHandler.cpp)
source_group(Engine FILES ${engine_source})

#TEngine/Change
set(change_headers
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TESubject.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TEObserver.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TEChangeMasks.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TEChangeSyncer.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TEChangeData.h)
source_group(Engine\\Change FILES ${change_headers})

set(change_source
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TESubject.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Change/TEChangeSyncer.cpp)
source_group(Engine\\Change FILES ${change_source})

#TEngine/System
set(systems_headers
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemTask.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystem.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemScene.h
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemObject.h)
source_group(Engine\\Systems FILES ${systems_headers})

set(systems_source
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemTask.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemObject.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystem.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Engine/Systems/TESystemScene.cpp)
source_group(Engine\\Systems FILES ${systems_source})

#TEngine/Event
set(event_headers
${TEngine_SOURCE_DIR}/Code/TEngine/Event/TEEventManager.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/TEEventHandler.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/TEQuedEvent.h)
source_group(Event FILES ${event_headers})

set(event_source
${TEngine_SOURCE_DIR}/Code/TEngine/Event/TEEventManager.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/TEEventHandler.cpp)
source_group(Event FILES ${event_source})

#TEngine/Events
set(events_headers
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEEventVisitor.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEResolutionEvent.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEAddForceEvent.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TETranslationEvent.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEScaleEvent.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEOrientationEvent.h
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEEnvironmentUpdateEvent.h)
source_group(Event\\Events FILES ${events_headers})

set(events_source
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEEventVisitor.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEResolutionEvent.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEAddForceEvent.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TETranslationEvent.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEScaleEvent.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEOrientationEvent.cpp
${TEngine_SOURCE_DIR}/Code/TEngine/Event/Events/TEEnvironmentUpdateEvent.cpp)
source_group(Event\\Events FILES ${events_source})

#TEngine/LuaInterface
set(luainterface_headers
${TEngine_SOURCE_DIR}/Code/TEngine/LuaInterface/TELuaInterface.h)
source_group(LuaInterface FILES ${luainterface_headers})

set(luainterface_source
${TEngine_SOURCE_DIR}/Code/TEngine/LuaInterface/TELuaInterface.cpp)
source_group(LuaInterface FILES ${luainterface_source})

#if(WIN32)
#	  include_directories(";$(DXSDK_DIR)Include")
#endif()

include_directories(
${tengine_dirs}
${tecore_dirs}
${teplatform_dirs}
${TEngine_SOURCE_DIR}/Externals/srdelegates/include
${external_luajit_include})

add_library(TEngine
${engine_headers}
${engine_source}
${change_headers}
${change_source}
${systems_headers}
${systems_source}
${events_headers}
${events_source}
${event_headers}
${event_source}
${luainterface_headers}
${luainterface_source})

if(WIN32)
    target_link_libraries(TEngine
                          TECore
                          TEPlatform)
elseif(UNIX)
    find_package(X11 REQUIRED)
    include_directories(SYSTEM ${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
    target_link_libraries(TEngine
                          TECore
                          TEPlatform)
endif()

if(MSVC)
	set_target_properties(TEngine PROPERTIES FOLDER "1. TEngine framework")
endif()
