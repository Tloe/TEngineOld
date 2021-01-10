
# include_directories(
# ${tecore_dirs}
# ${ENET_INCLUDE}
# ${LIBPNG_INCLUDE}
# ${external_luajit_include})

# add_library(TECore
# ${intersection_headers}
# ${intersection_source}
# ${images_headers}
# ${images_source}
# ${math_headers}
# ${resources_headers}
# ${resources_source}
# ${Lua_headers}
# ${Lua_source}
# ${image_headers}
# ${image_source}
# ${io_headers}
# ${io_source}
# ${threading_headers}
# ${threading_source}
# ${utils_headers}
# ${utils_source}
# ${network_headers}
# ${network_source})

#TODO! Add source_group for VS

add_library(TECore "")

add_subdirectory(Images)
add_subdirectory(Intersection)
add_subdirectory(IO)
add_subdirectory(Lua)
add_subdirectory(Math)
add_subdirectory(Network)
add_subdirectory(Resources)
add_subdirectory(Threading)
add_subdirectory(Utils)

if(WIN32)
    target_link_libraries(TECore ${LUA_LIBRARIES})
elseif(UNIX)
    find_package(Threads)
    target_link_libraries(TECore
        PUBLIC
            ${CMAKE_THREAD_LIBS_INIT} 
            ${CONAN_LIBS_LUAJIT}
            ${CONAN_LIBS_ENET}
            ${CONAN_LIBS_LIBPNG})

endif()

target_include_directories(TECore
    PUBLIC
        Images
        Intersection
        IO
        Lua
        Math
        Network
        Resources
        Threading
        Utils
    PRIVATE
        ${CONAN_INCLUDE_DIRS_LUAJIT}
        ${CONAN_INCLUDE_DIRS_ENET}
        ${CONAN_INCLUDE_DIRS_LIBPNG})

if(MSVC)
	set_target_properties(TECore PROPERTIES FOLDER "0. TELibs")
endif()
