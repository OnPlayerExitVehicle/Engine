cmake_minimum_required(VERSION 3.8)

project(Server)

set(PROJECT_SOURCES_DIR "./src")
set(PROJECT_SOURCES "${PROJECT_SOURCES_DIR}/Server.cpp")
set(NETWORKING_INCLUDE_DIR "../Networking/include")
set(PROJECT_EXECUTABLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../bin")

#include_directories(${NETWORKING_INCLUDE_DIR})

add_executable(Server ${PROJECT_SOURCES})
set_target_properties(Server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXECUTABLE_DIR})