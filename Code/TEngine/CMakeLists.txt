add_library(TEngine)

tengine_sourcegroup_init()

add_subdirectory(Engine)
add_subdirectory(Event)
add_subdirectory(LuaInterface)

tengine_sourcegroup_done()

target_link_libraries(TEngine PUBLIC TECore)

target_include_directories(TEngine
    PUBLIC
        Engine
        Engine/Change
        Engine/Systems
        Event
        Event/Events
        LuaInterface)

set_target_properties(TEngine PROPERTIES FOLDER "1. TEngine framework")
