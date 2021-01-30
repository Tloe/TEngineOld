set(HEADERS
    TELinuxWindow.h)
set(SOURCES
    TELinuxWindow.cpp)

target_sources(TEPlatform PUBLIC ${HEADERS} PRIVATE ${SOURCES} CMakeLists.txt)

target_sourcegroup_add()

message("LETS SEE?????")
if(MSVC)
    message("MSVC IT IS")
    set_source_files_properties(${SOURCES} DIRECTORY ${TARGET_ROOT} PROPERTIES HEADER_FILE_ONLY TRUE)
endif()