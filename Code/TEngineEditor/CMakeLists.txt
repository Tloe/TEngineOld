#/TEngineEditor

#TEngineEditor/DatFileManager
set(datmanager_headers
${TEngine_SOURCE_DIR}/Code/TEngineEditor/DatFileManagerWidget.h
${TEngine_SOURCE_DIR}/Code/TEngineEditor/DatFileModel.h)
source_group("DatManager" FILES ${datmanager_headers})

set(datmanager_source
${TEngine_SOURCE_DIR}/Code/TEngineEditor/DatFileManagerWidget.cpp
${TEngine_SOURCE_DIR}/Code/TEngineEditor/DatFileModel.cpp)
source_group("DatManager" FILES ${datmanager_source})

#TEngineEditor
set(main_headers
${TEngine_SOURCE_DIR}/Code/TEngineEditor/main.h
${TEngine_SOURCE_DIR}/Code/TEngineEditor/TEngineEditor.h
${TEngine_SOURCE_DIR}/Code/TEngineEditor/ConvertMeshFormatWidget.h
${TEngine_SOURCE_DIR}/Code/TEngineEditor/TERenderWidget.h)
source_group("Main" FILES ${main_headers})

set(main_source
${TEngine_SOURCE_DIR}/Code/TEngineEditor/main.cpp
${TEngine_SOURCE_DIR}/Code/TEngineEditor/TEngineEditor.cpp
${TEngine_SOURCE_DIR}/Code/TEngineEditor/ConvertMeshFormatWidget.cpp
${TEngine_SOURCE_DIR}/Code/TEngineEditor/TERenderWidget.cpp)
source_group("Main" FILES ${main_source})

#if(WIN32)
#	include_directories("$(DXSDK_DIR)Include")
#endif()

include_directories(
${TEngine_SOURCE_DIR}/Code/TEngineEditor/
${tecore_dirs}
${tegraphicssystem_dirs}
${tengine_dirs})

link_directories(
${TEngine_SOURCE_DIR}/Code/TEngineEditor/
${tecore_dirs}
${tegraphicssystem_dirs}
${tengine_dirs}
${CgGlLibPath})

#QT
#FIND_PACKAGE(Qt4 REQUIRED)
#QT4_WRAP_CPP(main_headers_MOC ${main_headers})
#QT4_WRAP_CPP(datmanager_headers_MOC ${datmanager_headers})
#include(${QT_USE_FILE})
#add_definitions(${QT_DEFINITIONS})

add_executable(TEngineEditor ${datmanager_headers} ${datmanager_headers_MOC} ${main_headers} ${main_headers_MOC} ${main_source} ${datmanager_source})

target_link_libraries(TEngineEditor TECore TEGraphics TEngine ${cg_libs} ${QT_LIBRARIES} ${external_assimp_lib} ${libpng_lib})

if(MSVC)
	set_target_properties(TEngineEditor PROPERTIES FOLDER "3. Tools")
endif()
