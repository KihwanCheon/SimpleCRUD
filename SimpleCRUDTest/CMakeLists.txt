cmake_minimum_required(VERSION 3.9)

project(SimpleCRUDTest)

set(CMAKE_CXX_STANDARD 11)

include_directories(../googletest/googletest/include)
include_directories(../googletest/googletest)
include_directories(../SimpleCRUD/src)
include_directories(../sqlite)

file(GLOB gtest_srcs
        ../googletest/googletest/src/gtest-all.cc)

file(GLOB test_case_srcs
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*Test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/*/*Test.cpp
        )

add_executable(${PROJECT_NAME} test_main.cpp ${gtest_srcs} ${test_case_srcs})

target_link_libraries(${PROJECT_NAME}
        libSimpleCRUD
        )