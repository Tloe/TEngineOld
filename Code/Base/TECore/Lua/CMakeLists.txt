set(HEADERS
    TELuaVariable.h
    TELuaTable.h
    TELuaExtended.h
    TELuaBaseFunction.h
    TELuaFunction.h
    TELuaState.h
    TELuaHelpers.h
    TELuaNative.h
    TELuaRef.h
    TELuaStackReseter.h
    TELuaClass.h
    TELuaConstructor.h
    TELuaDestructor.h
    TELuaClassFunction.h)
set(SOURCES
    TELuaVariable.cpp
    TELuaTable.cpp
    TELuaExtended.cpp
    TELuaFunction.cpp
    TELuaState.cpp
    TELuaHelpers.cpp
    TELuaNative.cpp
    TELuaRef.cpp
    TELuaStackReseter.cpp
    TELuaClass.cpp
    TELuaConstructor.cpp
    TELuaDestructor.cpp
    TELuaClassFunction.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()