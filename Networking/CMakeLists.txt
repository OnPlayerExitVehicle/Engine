cmake_minimum_required(VERSION 3.8)

project(Networking)

add_subdirectory("../Dependencies/Sheila" "./Sheila" EXCLUDE_FROM_ALL)

set(PROJECT_INCLUDE_DIR "./include")
set(CORE_INCLUDE_DIR "../Core/include")
set(DEPENDENCY_DIR "../Dependencies")


set(PROJECT_SOURCES_DIR "./src")
set(PROJECT_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib")

file(GLOB PROJECT_SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

include_directories(
	${PROJECT_INCLUDE_DIR} 
	${CORE_INCLUDE_DIR} 
	${DEPENDENCY_DIR} 
	${DEPENDENCY_DIR}/GLAD
	${DEPENDENCY_DIR}/IMGUI
	${DEPENDENCY_DIR}/GLFW
	${CORE_INCLUDE_DIR}/InternalComponents
	${CORE_INCLUDE_DIR}/Utilities
)
add_library(Networking STATIC ${PROJECT_SOURCES})
target_link_libraries(Networking Client)
set_property(TARGET Client PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(Networking PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})