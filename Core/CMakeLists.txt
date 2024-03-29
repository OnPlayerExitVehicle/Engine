﻿cmake_minimum_required (VERSION 3.8)

project(Core)

add_subdirectory("../Dependencies/Bullet" "./Bullet" EXCLUDE_FROM_ALL)
add_subdirectory("../Dependencies/GLM" "./GLM" EXCLUDE_FROM_ALL)
add_subdirectory("../Dependencies/GLFW" "./GLFW" EXCLUDE_FROM_ALL)

set(PROJECT_INCLUDE_DIR "./include")
set(PROJECT_SOURCES_DIR "./src")
set(PROJECT_DEPENDENCY_DIR "../Dependencies")
set(IMGUI_DIR ${PROJECT_DEPENDENCY_DIR}/IMGUI)

set(PROJECT_EXECUTABLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(NETWORKING_INCLUDE_DIR "../Networking/include")
file(GLOB IMGUI_SOURCEFILES ${IMGUI_DIR}/*.cpp)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(${PROJECT_INCLUDE_DIR} ${PROJECT_DEPENDENCY_DIR} ${PROJECT_DEPENDENCY_DIR}/Bullet/src/ ${PROJECT_DEPENDENCY_DIR}/IMGUI ${PROJECT_DEPENDENCY_DIR}/GLAD ${PROJECT_INCLUDE_DIR}/InternalComponents ${PROJECT_INCLUDE_DIR}/Utilities)

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)
file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)

#if(WIN32)
#	execute_process(COMMAND "windres" "app.rc" "-o" "app.o" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/icons")
#	list(APPEND PROJECT_SOURCES "./icons/app.o")
#endif()

if(WIN32)
	add_custom_command(
			OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/icons/app.o"
			COMMAND "windres"
			ARGS "app.rc" "-o" "app.o"
			DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/icons/app.rc" "${CMAKE_CURRENT_SOURCE_DIR}/icons/app.ico"
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/icons"
	)
	list(APPEND PROJECT_SOURCES "./icons/app.o")
endif()

if((CMAKE_BUILD_TYPE STREQUAL "Release") AND WIN32)
add_executable(
	Engine WIN32
	${PROJECT_SOURCES}
	${IMGUI_SOURCES}
	${IMGUI_DIR}/backends/imgui_impl_glfw.cpp 
	${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp 
	${PROJECT_DEPENDENCY_DIR}/GLAD/glad.c
)
else()
add_executable(
		Engine
		${PROJECT_SOURCES}
		${IMGUI_SOURCES}
		${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
		${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
		${PROJECT_DEPENDENCY_DIR}/GLAD/glad.c
)
endif()

target_link_libraries(Engine LinearMath BulletCollision BulletDynamics LinearMath BulletCollision glfw Networking)
if(WIN32)
	set_property(TARGET Engine PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET BulletCollision PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET BulletDynamics PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET LinearMath PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET glfw PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set_property(TARGET Networking PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	message("CMAKE BUILD TYPE = " ${CMAKE_BUILD_TYPE})
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		message("hi")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:WinMainCRTStartup")
		set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_EXECUTABLE_DIR})
	else()
		message("hiiii")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")
		set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_EXECUTABLE_DIR})
	endif()
else()
	set_property(TARGET Engine PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXECUTABLE_DIR})
endif()