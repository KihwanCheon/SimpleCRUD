cmake_minimum_required(VERSION 3.9)

project(SimpleCRUE)

set(CMAKE_CXX_STANDARD 98)


# https://github.com/azadkuh/sqlite-amalgamation.git

include(ExternalProject)

ExternalProject_Add(
        sqlite3
        GIT_REPOSITORY https://github.com/azadkuh/sqlite-amalgamation.git
        UPDATE_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)

ExternalProject_Get_Property(sqlite3 source_dir)


add_executable(SimpleCRUD main.cpp)