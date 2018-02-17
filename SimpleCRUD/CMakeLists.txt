cmake_minimum_required(VERSION 3.9)

project(SimpleCRUD)

set(CMAKE_CXX_STANDARD 98)

include_directories(../sqlite/.libs)
include_directories(../sqlite)

file(GLOB src_files src/*.cpp)

add_library(lib${PROJECT_NAME} STATIC ${src_files} )
target_link_libraries(lib${PROJECT_NAME} libsqlite3.a)
target_include_directories(lib${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} lib${PROJECT_NAME})
