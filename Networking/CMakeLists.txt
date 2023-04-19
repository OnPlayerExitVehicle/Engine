cmake_minimum_required(VERSION 3.8)

project(Networking)

set(PROJECT_INCLUDE_DIR "./include")
set(CORE_INCLUDE_DIR "../Core/include")
set(DEPENDENCY_DIR "../Dependencies")

set(PROJECT_SOURCES_DIR "./src")
set(PROJECT_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

set(PROJECT_SOURCES
	"${PROJECT_SOURCES_DIR}/NetworkDelegate.cpp"
	"${PROJECT_SOURCES_DIR}/NetworkComponent.cpp"
	"${PROJECT_SOURCES_DIR}/NetworkTransform.cpp"
)

include_directories(${PROJECT_INCLUDE_DIR} ${CORE_INCLUDE_DIR} ${DEPENDENCY_DIR})
add_library(Networking STATIC ${PROJECT_SOURCES})
set_target_properties(Networking PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})