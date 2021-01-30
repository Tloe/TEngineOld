add_library(TECore)

target_sourcegroup_init()

add_subdirectory(Images)
add_subdirectory(Intersection)
add_subdirectory(IO)
add_subdirectory(Lua)
add_subdirectory(Math)
add_subdirectory(Network)
add_subdirectory(Resources)
add_subdirectory(Threading)
add_subdirectory(Utils)

target_sourcegroup_done()

if(WIN32)
    target_link_libraries(TECore
        PUBLIC
            CONAN_PKG::luajit
            CONAN_PKG::libpng
            CONAN_PKG::enet)
elseif(UNIX)
    #find_package(Threads)
    target_link_libraries(TECore
        PUBLIC
            luajit::luajit)

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
        Utils)

if(MSVC)
	set_target_properties(TECore PROPERTIES FOLDER "0. TELibs")
endif()
