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
target_link_libraries(csv2sqlite3 convLib db2Lib sqlite3)

enable_testing()

add_test(tests ${PROJECT_BINARY_DIR}/test)
set_tests_properties(tests PROPERTIES         ENVIRONMENT
                     DATADIR=${CMAKE_CURRENT_SOURCE_DIR}/data)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Packing)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" OFF)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
