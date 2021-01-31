set(HEADERS
    TELinuxWindow.h)
set(SOURCES
    TELinuxWindow.cpp)

target_sources(TEPlatform PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

tengine_sourcegroup_add()

if(MSVC)
    set_source_files_properties(${HEADERS} ${SOURCES} DIRECTORY ${TARGET_ROOT} PROPERTIES HEADER_FILE_ONLY TRUE)
endif()
