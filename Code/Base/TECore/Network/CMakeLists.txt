set(HEADERS
    TEReliabilityControl.h
    TEFlowControl.h
    TEReliableConnection.h
    TEAddress.h
    TEClient.h
    TEServer.h
    TEPacket.h
    TEPacketQue.h
    TEConnection.h
    TESocket.h
    TESocketIncludes.h)
set(SOURCES
    TEReliabilityControl.cpp
    TEFlowControl.cpp
    TEReliableConnection.cpp
    TEAddress.cpp
    TEClient.cpp
    TEServer.cpp
    TEPacket.cpp
    TEPacketQue.cpp
    TEConnection.cpp
    TESocket.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()