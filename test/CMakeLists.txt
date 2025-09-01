file( GLOB system_SOURCES *.cpp )
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
include(GoogleTest)
include(CTest)

find_program(LCOV lcov)
find_program(GENHTML genhtml)


add_library( testLib ${system_SOURCES} )
include_directories("${PROJECT_SOURCE_DIR} /include ")#/lib/gtest/googletest/include/gtest/")
target_include_directories(testLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")

add_executable(db_runner test_dbService.cpp )
target_link_libraries(db_runner  LINK_PUBLIC   gtest gtest_main  db2Lib sqlite3)
target_include_directories(db_runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")
target_compile_options(db_runner PRIVATE -coverage)
target_link_options(db_runner PRIVATE -coverage)

gtest_discover_tests(db_runner "" AUTO)

add_executable(conver_runner test_convService.cpp )
target_link_libraries(conver_runner  LINK_PUBLIC convLib db2Lib gtest gtest_main   sqlite3)
target_include_directories(conver_runner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include) # "/lib/gtest/googletest/include/gtest/")
target_compile_options(conver_runner PRIVATE -coverage)
target_link_options(conver_runner PRIVATE -coverage)


gtest_discover_tests(conver_runner "" AUTO)

set_tests_properties(${noArgsTests} PROPERTIES ENVIRONMENT
    DATADIR=${CMAKE_CURRENT_SOURCE_DIR}/data)


if(LCOV AND GENHTML)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory coverage
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${LCOV} --ignore-errors mismatch --capture --directory . --output-file coverage/coverage.info
        COMMAND ${LCOV} --remove coverage/coverage.info '/usr/*' '*gtest*' --output-file coverage/coverage_filtered.info
        COMMAND ${GENHTML} coverage/coverage_filtered.info --output-directory coverage/html
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating coverage report"
    )
else()
    message(WARNING "lcov or genhtml not found, coverage report generation disabled")
endif()

find_program(GCOVR gcovr)

if(GCOVR)
    add_custom_target(coverage_xml
        COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
        COMMAND ${GCOVR} --xml --output coverage/coverage.xml
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating XML coverage report"
    )
endif()