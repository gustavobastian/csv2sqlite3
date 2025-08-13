file( GLOB system_SOURCES *.cpp )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

add_library( testLib ${system_SOURCES} )
include_directories("${PROJECT_SOURCE_DIR} /include ")#/lib/gtest/googletest/include/gtest/")
target_include_directories(testLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")

add_executable(db_runner test_dbService.cpp )
target_link_libraries(db_runner  LINK_PUBLIC   gtest gtest_main  db2Lib sqlite3)
target_include_directories(db_runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")
add_test(NAME db_runner
    COMMAND db_runner)

add_executable(conver_runner test_convService.cpp )
target_link_libraries(conver_runner  LINK_PUBLIC convLib db2Lib gtest gtest_main   sqlite3)
target_include_directories(conver_runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")
add_test(NAME conver_runner
    COMMAND conver_runner)


set_tests_properties(conver_runner PROPERTIES ENVIRONMENT
    DATADIR=${CMAKE_CURRENT_SOURCE_DIR}/data)
set_tests_properties(db_runner PROPERTIES ENVIRONMENT
    DATADIR=${CMAKE_CURRENT_SOURCE_DIR}/data)