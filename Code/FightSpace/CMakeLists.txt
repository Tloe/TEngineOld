#/MainProject

set(main_headers
${TEngine_SOURCE_DIR}/Code/FightSpace/main.h)

set(main_source
${TEngine_SOURCE_DIR}/Code/FightSpace/main.cpp)

include_directories(
${TEngine_SOURCE_DIR}/Code/FightSpace/
${tecore_dirs}
${teplatform_dirs}
${tengine_dirs}
${terendering_dirs}
${tephysics_dirs}
${tegraphicssystem_dirs}
${tetransformsystem_dirs}
${tenetworksystem_dirs}
${tegamesystem_dirs}
${external_glew_include}
${CG_INCLUDE_PATH}
${external_luajit_include})

add_executable(FightSpace ${main_headers} ${main_source})

if(WIN32)
    set(directx_lib d3d11.lib)
    target_link_libraries(
        FightSpace
        TECore
        TEngine
        TEPhysics
        TEPlatform
        TEGraphicsSystem
        TETransformSystem
        TENetworkSystem
        TEGameSystem
        ${cg_libs}
        ${libpng_lib}
        ${directx_lib}
        ${winsock2_lib}
        ${external_luajit_lib})
elseif(UNIX)
    target_link_libraries(
        FightSpace
        TECore
        TEngine
        TEPhysics
        TEPlatform
        TEGraphicsSystem
        TETransformSystem
        TENetworkSystem
        TEGameSystem
        ${external_luajit_lib}
        ${cg_libs}
        ${libpng_lib}
        ${Boost_SYSTEM_LIBRARY}
        -L/usr/lib64
        -lXxf86vm)
endif()

if(MSVC)
	#set_target_properties(FightSpace PROPERTIES PLATFORM_TOOLSET "v120_CTP_Nov2012")
	set_target_properties(FightSpace PROPERTIES FOLDER "4. Applications")
endif()
