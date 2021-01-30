set(HEADERS
    TEHelpers.h
    TEMathBase.h
    TEMatrix3D.h
    TEMatrix4D.h
    TEQuaternion.h
    TETransform.h
    TEVector2D.h
    TEVector3D.h)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE CMakeLists.txt)

target_sourcegroup_add()