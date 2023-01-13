cmake_minimum_required( VERSION 3.2 )
PROJECT( sqlite3 )

include_directories( ${CMAKE_SOURCE_DIR}/libraries/sqlite3 )
add_library( sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h )
target_link_libraries( sqlite3 )