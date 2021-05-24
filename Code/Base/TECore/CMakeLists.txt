add_library(TECore)

tengine_sourcegroup_init()

add_subdirectory(Images)
add_subdirectory(Intersection)
add_subdirectory(IO)
add_subdirectory(Lua)
add_subdirectory(Math)
add_subdirectory(Network)
add_subdirectory(Resources)
add_subdirectory(Threading)
add_subdirectory(Utils)

tengine_sourcegroup_done()

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(TECore
  PUBLIC
    CONAN_PKG::luajit
    CONAN_PKG::libpng
  PRIVATE
    ${CMAKE_THREAD_LIBS_INIT})

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

set_target_properties(TECore PROPERTIES FOLDER "0. TELibs")
