add_executable(Testing)

set(SOURCES
  main.cpp)

target_sources(Testing PRIVATE ${SOURCES})

tengine_sourcegroup_init()
tengine_sourcegroup_add()
tengine_sourcegroup_done()

target_link_libraries(Testing
  PUBLIC CONAN_PKG::catch2
  PRIVATE TECore)

if(MSVC)
    set_target_properties(Testing
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG
        "${TEngine_SOURCE_DIR}/Executables")
    set_target_properties(Testing
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE
        "${TEngine_SOURCE_DIR}/Executables")
else()
    set_target_properties(Testing
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY
        "${TEngine_SOURCE_DIR}/Executables")
endif()

set_target_properties(Testing PROPERTIES FOLDER "4. Applications")
