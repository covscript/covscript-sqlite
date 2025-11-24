cmake_minimum_required(VERSION 3.16)

project(covscript-sqlite)
include_directories(include)

if (DEFINED ENV{CS_DEV_PATH})
    message("-- CovScript SDK detected at $ENV{CS_DEV_PATH}")
    include("$ENV{CS_DEV_PATH}/csbuild.cmake")
    include_directories($ENV{CS_DEV_PATH}/include)
    link_directories($ENV{CS_DEV_PATH}/lib)
else ()
    message(FATAL_ERROR "-- CovScript SDK not detected. Please set environment variable CS_DEV_PATH")
endif ()

add_library(sqlite SHARED sqlite.cpp sqlite3.c)

target_link_libraries(sqlite covscript)

if (UNIX)
    target_link_libraries(sqlite pthread)
endif ()

set_target_properties(sqlite PROPERTIES OUTPUT_NAME sqlite)
set_target_properties(sqlite PROPERTIES PREFIX "")
set_target_properties(sqlite PROPERTIES SUFFIX ".cse")