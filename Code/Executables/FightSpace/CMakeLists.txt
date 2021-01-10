add_executable(FightSpace "")

target_sources(FightSpace
    PUBLIC
        main.h
    PRIVATE
        main.cpp)

target_include_directories(FightSpace
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})


target_link_libraries(FightSpace
    PUBLIC
        TEGraphicsSystem
        TETransformSystem
        TENetworkSystem
        TEGameSystem
        ${CONAN_LIBS})

if(MSVC)
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG
        "${TEngine_SOURCE_DIR}/Executables")
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        "${TEngine_SOURCE_DIR}/Executables")
else()
    set_target_properties(FightSpace
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        "${TEngine_SOURCE_DIR}/Executables")
endif()

# if(WIN32)
#     set(directx_lib d3d11.lib)
#     target_link_libraries(
#         FightSpace
#         TECore
#         TEngine
#         TEPhysics
#         TEPlatform
#         TEGraphicsSystem
#         TETransformSystem
#         TENetworkSystem
#         TEGameSystem
#         ${libpng_lib}
#         ${directx_lib}
#         ${winsock2_lib}
#         ${external_luajit_lib})
# elseif(UNIX)
#     find_package(Threads)
# 	find_package(X11 REQUIRED)
#     include_directories(SYSTEM ${X11_INCLUDE_DIR})
#     target_link_libraries(
#         FightSpace
#         TECore
#         TEngine
#         TEPhysics
#         TEPlatform
#         TEGraphicsSystem
#         TETransformSystem
#         TENetworkSystem
#         TEGameSystem
#         ${external_luajit_lib}
#         ${libpng_lib}
#         ${Boost_SYSTEM_LIBRARY}
#         ${X11_LIBRARIES}
#         ${X11_Xxf86vm_LIB}
#         ${CMAKE_THREAD_LIBS_INIT})
# endif()

if(MSVC)
	#set_target_properties(FightSpace PROPERTIES PLATFORM_TOOLSET "v120_CTP_Nov2012")
	set_target_properties(FightSpace PROPERTIES FOLDER "4. Applications")
endif()
