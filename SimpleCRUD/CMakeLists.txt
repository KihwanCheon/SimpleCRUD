cmake_minimum_required(VERSION 3.9)

project(SimpleCRUD)

set(CMAKE_CXX_STANDARD 11)
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
endif()

include_directories(../sqlite)
include_directories(./src)

file(GLOB src_files ./src/*.cpp)
file(GLOB sqlite_src_files ../sqlite/*.c)

add_library(sqlite3ex STATIC ${sqlite_src_files})
add_library(${PROJECT_NAME} STATIC ${src_files} )

if (WIN32)
    target_link_libraries(${PROJECT_NAME} sqlite3ex)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    add_executable(bin${PROJECT_NAME} main.cpp)
    target_link_libraries(bin${PROJECT_NAME} ${PROJECT_NAME})
else()
    find_package (Threads REQUIRED)

    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} dl sqlite3ex)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

    add_executable(bin${PROJECT_NAME} main.cpp)
    target_link_libraries(bin${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} dl sqlite3ex ${PROJECT_NAME})
endif()