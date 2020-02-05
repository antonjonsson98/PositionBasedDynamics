#--------------------------------------------------------------------------
# Skeleton project
#--------------------------------------------------------------------------

PROJECT(Main)
FILE(GLOB Main_headers code/*.h)
FILE(GLOB Main_sources code/*.cc)
FILE(GLOB res code/res/*.*)

SET(files_Main ${Main_headers} ${Main_sources})
SOURCE_GROUP("Main" FILES ${files_Main})

foreach(FILE ${res})
    configure_file(${FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach(FILE)

ADD_EXECUTABLE(Main ${files_Main})
TARGET_LINK_LIBRARIES(Main core render)
ADD_DEPENDENCIES(Main core render)
