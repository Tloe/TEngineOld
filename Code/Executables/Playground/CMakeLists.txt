#/MainProject

set(main_headers
${TEngine_SOURCE_DIR}/Code/Testing/main.h
${TEngine_SOURCE_DIR}/Code/Testing/NetworkTest.h
${TEngine_SOURCE_DIR}/Code/Testing/RandomTesting.h
${TEngine_SOURCE_DIR}/Code/Testing/AssetImporterTest.h
${TEngine_SOURCE_DIR}/Code/Testing/TEAssetImporter.h)
#source_group(Headers FILES ${main_headers})

set(main_source
${TEngine_SOURCE_DIR}/Code/Testing/main.cpp
${TEngine_SOURCE_DIR}/Code/Testing/NetworkTest.cpp
${TEngine_SOURCE_DIR}/Code/Testing/RandomTesting.cpp
${TEngine_SOURCE_DIR}/Code/Testing/AssetImporterTest.cpp
${TEngine_SOURCE_DIR}/Code/Testing/TEAssetImporter.cpp)
#source_group(Source FILES ${main_source})

include_directories(
${TEngine_SOURCE_DIR}/Code/Testing/
${tecore_dirs}
${teplatform_dirs}
${tengine_dirs}
${terendering_dirs}
${tephysics_dirs}
${tegraphicssystem_dirs}
${tetransformsystem_dirs}
${tenetworksystem_dirs}
${external_assimp_include})

add_executable(Testing ${main_headers} ${main_source})

if(WIN32)
	set(directx_lib d3d11.lib)
	target_link_libraries(
		Testing
		TECore
		TEngine
		TEGraphicsSystem
		TEPhysics
		TETransformSystem
		TEPlatform
		${cg_libs}
		${libpng_lib}
		${directx_lib}
		${winsock2_lib}
		debug ${external_assimp_lib_D}
		optimized ${external_assimp_lib_R})
elseif(UNIX)
	target_link_libraries(
		Testing
		TECore
		TEngine
		TEGraphicsSystem
		TEPhysics
		TETransformSystem
		TEPlatform
                ${external_assimp_lib}
                ${Boost_SYSTEM_LIBRARY}
                ${Boost_THREAD_LIBRARY}
                ${libpng_lib}
                -L/usr/lib64)
endif()

if(MSVC)
	set_target_properties(Testing PROPERTIES FOLDER "4. Applications")
endif()
