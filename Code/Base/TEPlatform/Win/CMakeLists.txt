set(HEADERS
    TEWinWindow.h)
set(SOURCES
    TEWinWindow.cpp)

target_sources(TEPlatform PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()

if(UNIX)
    set_source_files_properties(${SOURCES} DIRECTORY ${TARGET_ROOT} PROPERTIES HEADER_FILE_ONLY TRUE)    
endif()
