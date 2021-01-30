set(HEADERS
    TEFileIO.h
    TEDatFile.h
    TEDatPath.h
    TEFileSystemIO.h
    TEDatFileIO.h
    TEFile.h
    TEJson.h)
set(SOURCES
    TEFileIO.cpp
    TEDatPath.cpp
    TEDatFile.cpp
    TEFileSystemIO.cpp
    TEDatFileIO.cpp
    TEFile.cpp
    TEJson.cpp)

target_sources(TECore PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()