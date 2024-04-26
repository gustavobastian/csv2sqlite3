file( GLOB system_SOURCES *.cpp )

add_library( convLib ${system_SOURCES} )
target_include_directories(convLib PUBLIC sqlite3 db2Lib ${CMAKE_CURRENT_SOURCE_DIR} )

