#TEPlatform

set(common_headers
${TEngine_SOURCE_DIR}/Code/TEPlatform/TEPlatformWindowIncludes.h)
source_group(Common FILES ${common_headers})

set(inputmapping_headers
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInputContext.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInputMapper.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEActionExecutor.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEStateExecutor.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TERangeExecutor.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEAction.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEState.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TERange.h
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInput.h)
source_group(InputMapping FILES ${inputmapping_headers})

set(inputmapping_source
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInputContext.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInputMapper.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEActionExecutor.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEStateExecutor.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TERangeExecutor.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TERange.cpp
${TEngine_SOURCE_DIR}/Code/TEPlatform/InputMapping/TEInput.cpp)
source_group(InputMapping FILES ${inputmapping_source})

set(winplatform_headers
${TEngine_SOURCE_DIR}/Code/TEPlatform/Win/TEWinWindow.h)
source_group(Win FILES ${winplatform_headers})

set(winplatform_source
${TEngine_SOURCE_DIR}/Code/TEPlatform/Win/TEWinWindow.cpp
)
source_group(Win FILES ${winplatform_source})

set(linuxplatform_headers
${TEngine_SOURCE_DIR}/Code/TEPlatform/Linux/TELinuxWindow.h
)
source_group(Linux FILES ${linuxplatform_headers})

set(linuxplatform_source
${TEngine_SOURCE_DIR}/Code/TEPlatform/Linux/TELinuxWindow.cpp
)
source_group(Linux FILES ${linuxplatform_source})

include_directories(
${teplatform_dirs}
${tecore_dirs})

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
if(MSVC)
	set(library_files
	${common_headers}
	${inputmapping_headers}
	${inputmapping_source}
	${winplatform_headers}
	${winplatform_source})
endif()

if(UNIX)
 #       set_source_files_properties(
 #               ${winplatform_headers}
 #              ${winplatform_source}
 #             PROPERTIES HEADER_FILE_ONLY true)
 
		set(library_files
			${common_headers}
			${inputmapping_headers}
			${inputmapping_source}
			${winplatform_headers}
			${winplatform_source})

        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        link_directories(${X11_LIBRARIES})
endif()

add_library(TEPlatform
	${library_files})

if(WIN32)
        target_link_libraries(TEPlatform)
elseif(UNIX)
        target_link_libraries(TEPlatform)
endif()

if(MSVC)
#	add_dependencies(TEPlatform ExcludeFilesFromTEPlatform)
	set_target_properties(TEPlatform PROPERTIES FOLDER "0. TELibs")
#	set_target_properties(ExcludeFilesFromTEPlatform PROPERTIES FOLDER "9. CMake")
endif()
