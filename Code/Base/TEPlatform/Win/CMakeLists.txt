target_sources(TEPlatform
    PUBLIC
        TEWinWindow.h
    PRIVATE
        TEWinWindow.cpp
)

if(UNIX)
    set_source_files_properties(TEWinWindow.h
                                TEWinWindow.cpp
                                PROPERTIES HEADER_FILE_ONLY true)
endif()
