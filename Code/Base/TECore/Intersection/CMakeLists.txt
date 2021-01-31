set(HEADERS
    TEBSphere.h
    TECollider.h
    TEColliderVisitor.h
    TESphereObbCollider.h
    TESpherePlaneCollider.h
    TESphereSphereCollider.h
    TEContactSet.h
    TEIntersectionConfig.h
    TEObb.h
    TEObbObbCollider.h
    TEObbPlaneCollider.h
    TEPlane.h)
set(SOURCES
    TEBSphere.cpp
    TEColliderVisitor.cpp
    TESphereObbCollider.cpp
    TESpherePlaneCollider.cpp
    TESphereSphereCollider.cpp
    TEObb.cpp
    TEObbObbCollider.cpp
    TEObbPlaneCollider.cpp
    TEPlane.cpp
    TEIntersectionConfig.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()


