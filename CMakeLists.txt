cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME "crocus")
set(PROJECT_PATH      ${CMAKE_SOURCE_DIR} )
set(PROJECT_OUT_PATH  ${CMAKE_BINARY_DIR} )
set(PROJECT_INCLUDES  "include" )
set(PROJECT_LIBRARIES  "" )
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")
#SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

FILE( GLOB_RECURSE PROJECT_SOURCES src/rule/*.cpp src/*.cpp)
FILE( GLOB_RECURSE PROJECT_TEST_SOURCES test/**/*.c test/**/*.cpp)
FILE( GLOB_RECURSE PROJECT_HEADERS include/*.h )

project(${PROJECT_NAME})

include_directories(${PROJECT_INCLUDES})

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild)

set(testSources test/*.cpp)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
