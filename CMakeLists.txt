cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME "crocus")
set(SFML_CLIENT_NAME "sfmlcrocus")
set(PROJECT_PATH      ${CMAKE_SOURCE_DIR} )
set(PROJECT_OUT_PATH  ${CMAKE_BINARY_DIR} )
set(PROJECT_INCLUDES  "include" )
set(PROJECT_LIBRARIES  "" )
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

#SET(GCC_COVERAGE_COMPILE_FLAGS "-O2")
#SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

FILE( GLOB_RECURSE PROJECT_SOURCES src/core/*.cpp)
FILE( GLOB_RECURSE PROJECT_CLIENT_SOURCES src/client/*.cpp)
FILE( GLOB_RECURSE PROJECT_TEST_SOURCES test/*.cpp)
FILE( GLOB_RECURSE PROJECT_HEADERS include/*.h )

project(${PROJECT_NAME})

include_directories(${PROJECT_INCLUDES})

set(testSources test/*.cpp)

set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)


add_library(lib${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
set_target_properties(lib${PROJECT_NAME} PROPERTIES PREFIX "")

add_executable(${PROJECT_NAME} src/main/main.cpp )
target_link_libraries(${PROJECT_NAME} lib${PROJECT_NAME})

add_executable(${SFML_CLIENT_NAME} ${PROJECT_CLIENT_SOURCES})
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${SFML_CLIENT_NAME} lib${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()







# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
#    URL https://github.com/google/googletest/archive/master.zip
    URL http://785i0w.com1.z0.glb.clouddn.com/googletest-master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

#set(source_dir build/gtest/src/gtest)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

add_executable(test${PROJECT_NAME} ${PROJECT_TEST_SOURCES})

target_link_libraries(test${PROJECT_NAME}
    lib${PROJECT_NAME}
    libgtest
    libgmock
)

install(TARGETS test${PROJECT_NAME} DESTINATION bin)

include(check-format.cmake)
