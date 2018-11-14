#TEInputSystem

set(inputsystem_headers
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputObject.h
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputSystem.h
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputScene.h
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputTask.h
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputProperties.h
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEActions.h
)

set(inputsystem_source
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputObject.cpp
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputSystem.cpp
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputScene.cpp
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEInputTask.cpp
${TEngine_SOURCE_DIR}/Code/TEInputSystem/TEActions.cpp
)

include_directories(
${teinputsystem_dirs}
${tecore_dirs}
${teplatform_dirs}
${tengine_dirs}
${external_jsoncpp_include}
)

add_library(TEInputSystem
${inputsystem_headers}
${inputsystem_source})

if(WIN32)
	target_link_libraries(
		TEInputSystem
		TECore
		TEPlatform
		TEngine
		debug ${external_jsoncpp_lib_D}
		optimized ${external_jsoncpp_lib_R})
elseif(UNIX)
	target_link_libraries(
		TEInputSystem
		TECore
		TEPlatform
		TEngine
		${external_jsoncpp_lib})
endif()

if(MSVC)
	set_target_properties(TEInputSystem PROPERTIES FOLDER "2. TEngine Systems")
endif()