#TETransformSystem

set(transformsystem_headers
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformSystem.h
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformObject.h
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformScene.h
)

set(transformsystem_source
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformSystem.cpp
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformObject.cpp
${TEngine_SOURCE_DIR}/Code/TETransformSystem/TETransformScene.cpp
)

include_directories(
${tetransformsystem_dirs}
${tengine_dirs}
${tecore_dirs}
${external_jsoncpp_include}
${external_luajit_include})

add_library(TETransformSystem
${transformsystem_headers}
${transformsystem_source})

target_link_libraries(TETransformSystem TECore TEngine)

if(MSVC)
	set_target_properties(TETransformSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()
