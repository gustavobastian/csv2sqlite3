cmake_minimum_required(VERSION 3.15)
project(csv2sqlite3 VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)


include_directories("${PROJECT_SOURCE_DIR}/include" "${PROJECT_BUILD_DIR}/include" "/lib/gtest/googletest/include/gtest" "${PROJECT_BUILD_DIR}/lib/gtest/googletest/include")



add_subdirectory( src/convService )
add_subdirectory( src/dbService )
add_subdirectory( lib/gtest )
add_subdirectory( test/ )

add_executable(csv2sqlite3 src/main.cpp)

target_include_directories(csv2sqlite3 PUBLIC  /include /lib/gtest/googletest/include/gtest)

enable_testing()

add_test(tests ${PROJECT_BINARY_DIR}/test)
set_tests_properties(tests PROPERTIES         ENVIRONMENT
                     DATADIR=${CMAKE_CURRENT_SOURCE_DIR}/data)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

