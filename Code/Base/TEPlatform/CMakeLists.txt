add_library(TEPlatform "")

target_sources(TEPlatform
    PUBLIC
        TEPlatformWindowIncludes.h
)

#set_source_files_properties(${platform_headers} PROPERTIES HEADER_FILE_ONLY true)

#if(MSVC)
 #       set(Exclude_MSVC_Linux
 #               ${linuxplatform_headers}
 #               ${linuxplatform_source})

 #       set(filecontent "ALL ${Exclude_MSVC_Linux} DebugOpenGL ReleaseOpenGL DebugDX11 ReleaseDX11 ")
 #       string(REPLACE ";" " " filecontent "${filecontent}")
 #       string(REPLACE "${TEngine_SOURCE_DIR}/Code/TEPlatform/Linux/" "" filecontent "${filecontent}")
 #       file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/PlatformExcludes.txt "${filecontent}")
 #       add_custom_target(ExcludeFilesFromTEPlatform ALL
 #       COMMAND ${TEngine_SOURCE_DIR}/Utils/CMake/ExcludeFilesFromProject.exe ${CMAKE_CURRENT_BINARY_DIR}/TEPlatform.vcxproj ${CMAKE_CURRENT_BINARY_DIR}/PlatformExcludes.txt)
#endif()

if(UNIX)
    find_package(X11 REQUIRED)
    set(platform_SUBDIR Linux)
    set(platform_INCLUDES ${X11_INCLUDE_DIR})
    set(platform_LIBRARIES ${X11_LIBRARIES} ${X11_Xxf86vm_LIB})

elseif(WIN32)
    set(platform_SUBDIR Win)
endif()

add_subdirectory(InputMapping)
add_subdirectory(${platform_SUBDIR})

target_link_libraries(TEPlatform
    PUBLIC
        ${platform_LIBRARIES}
        TECore)

target_include_directories(TEPlatform
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        InputMapping
        ${platform_SUBDIR}
    SYSTEM PUBLIC
        ${platform_INCLUDES})

if(MSVC)
#	add_dependencies(TEPlatform ExcludeFilesFromTEPlatform)
	set_target_properties(TEPlatform PROPERTIES FOLDER "0. TELibs")
#	set_target_properties(ExcludeFilesFromTEPlatform PROPERTIES FOLDER "9. CMake")
endif()
