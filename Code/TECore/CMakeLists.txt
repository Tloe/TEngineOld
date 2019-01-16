#TECore/src

#TECore/intersection
set(intersection_headers
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEBSphere.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TECollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEColliderVisitor.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESphereObbCollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESpherePlaneCollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESphereSphereCollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEContactSet.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEIntersectionConfig.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObb.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObbObbCollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObbPlaneCollider.h
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEPlane.h)
source_group(Intersection FILES ${intersection_headers})

set(intersection_source
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEBSphere.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEColliderVisitor.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESphereObbCollider.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESpherePlaneCollider.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TESphereSphereCollider.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObb.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObbObbCollider.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEObbPlaneCollider.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEPlane.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Intersection/TEIntersectionConfig.cpp)
source_group(Intersection FILES ${intersection_source})

#TECore/lua
set(Lua_headers
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaVariable.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaTable.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaExtended.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaBaseFunction.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaFunction.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaState.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaHelpers.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaNative.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaRef.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaStackReseter.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaClass.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaConstructor.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaDestructor.h
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaClassFunction.h)
source_group(Lua FILES ${Lua_headers})

set(Lua_source
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaVariable.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaTable.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaExtended.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaFunction.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaState.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaHelpers.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaNative.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaRef.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaStackReseter.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaClass.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaConstructor.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaDestructor.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Lua/TELuaClassFunction.cpp)
source_group(Lua FILES ${Lua_source})

#TECore/images
set(images_headers
${TEngine_SOURCE_DIR}/Code/TECore/Images/TEImage.h
${TEngine_SOURCE_DIR}/Code/TECore/Images/TEImagePNG.h)
source_group(Images FILES ${images_headers})

set(images_source
${TEngine_SOURCE_DIR}/Code/TECore/Images/TEImagePNG.cpp)
source_group(Images FILES ${images_source})

#TECore/Math
set(math_headers
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEHelpers.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEMathBase.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEMatrix3D.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEMatrix4D.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEQuaternion.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TETransform.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEVector2D.h
${TEngine_SOURCE_DIR}/Code/TECore/Math/TEVector3D.h)
source_group(Math FILES ${math_headers})

#TECore/Resources
set(resources_headers
${TEngine_SOURCE_DIR}/Code/TECore/Resources/TEResource.h
${TEngine_SOURCE_DIR}/Code/TECore/Resources/TEResourceHandle.h
${TEngine_SOURCE_DIR}/Code/TECore/Resources/TEResourceManager.h
${TEngine_SOURCE_DIR}/Code/TECore/Resources/TECrypto.h)
source_group(Resources FILES ${resources_headers})

set(resources_source
${TEngine_SOURCE_DIR}/Code/TECore/Resources/TEResource.cpp)
source_group(Resources FILES ${resources_source})

#TECore/IO
set(io_headers
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFileIO.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatFile.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatPath.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFileSystemIO.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatFileIO.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFile.h
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEJson.h)
source_group(IO FILES ${io_headers})

set(io_source
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFileIO.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatPath.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatFile.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFileSystemIO.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEDatFileIO.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEFile.cpp
${TEngine_SOURCE_DIR}/Code/TECore/IO/TEJson.cpp)
source_group(IO FILES ${io_source})

#TECore/Threading
set(threading_headers
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TELockQue.h
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEThreadPool.h
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEWorkStealingQue.h
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEFunctionWrapper.h
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEThreadJoiner.h
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEFutureJoiner.h)
source_group(Threading FILES ${threading_headers})

set(threading_source
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEThreadPool.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEWorkStealingQue.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Threading/TEFunctionWrapper.cpp)
source_group(Threading FILES ${threading_source})

#TECore/Utils
set(utils_headers
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEVariant.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TECircularQue.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEValue.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEColor.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TETypeid.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEDataTypes.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TETimer.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TETime.h
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TERandomNumberGenerators.h)
source_group(Utils FILES ${utils_headers})

#TECore/Utils
set(utils_source
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEVariant.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEValue.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TEDataTypes.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TETimer.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Utils/TETime.cpp)
source_group(Utils FILES ${utils_source})

#TECore/Network
set(network_headers
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEReliabilityControl.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEFlowControl.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEReliableConnection.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEAddress.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEClient.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEServer.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEPacket.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEPacketQue.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEConnection.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TESocket.h
${TEngine_SOURCE_DIR}/Code/TECore/Network/TESocketIncludes.h)
source_group(Network FILES ${network_headers})

set(network_source
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEReliabilityControl.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEFlowControl.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEReliableConnection.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEAddress.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEClient.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEServer.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEPacket.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEPacketQue.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TEConnection.cpp
${TEngine_SOURCE_DIR}/Code/TECore/Network/TESocket.cpp)
source_group(Network FILES ${network_source})

include_directories(
${tecore_dirs}
${ENET_INCLUDE}
${LIBPNG_INCLUDE}
${external_luajit_include})

add_library(TECore
${intersection_headers}
${intersection_source}
${images_headers}
${images_source}
${math_headers}
${resources_headers}
${resources_source}
${Lua_headers}
${Lua_source}
${image_headers}
${image_source}
${io_headers}
${io_source}
${threading_headers}
${threading_source}
${utils_headers}
${utils_source}
${network_headers}
${network_source})

if(WIN32)
    target_link_libraries(TECore ${winsock2_lib} ${LUA_LIBRARIES})
elseif(UNIX)
    target_link_libraries(TECore ${libpng_lib} ${Boost_CHRONO_LIBRARY} ${LUA_LIBRARIES})
endif()

if(MSVC)
	set_target_properties(TECore PROPERTIES FOLDER "0. TELibs")
endif()
