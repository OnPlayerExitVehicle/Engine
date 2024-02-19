cmake_minimum_required (VERSION 3.8)

project(Core)

add_subdirectory("../Dependencies/Bullet" "./Bullet")
add_subdirectory("../Dependencies/GLM" "./GLM")
add_subdirectory("../Dependencies/GLFW" "./GLFW")

set(PROJECT_INCLUDE_DIR "./include")
set(PROJECT_SOURCES_DIR "./src")
set(PROJECT_DEPENDENCY_DIR "../Dependencies")
set(BULLET_LIBRARY_DIR "${PROJECT_DEPENDENCY_DIR}/Bullet/build/src")
set(IMGUI_DIR ${PROJECT_DEPENDENCY_DIR}/IMGUI)

set(PROJECT_EXECUTABLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(NETWORKING_INCLUDE_DIR "../Networking/include")
file(GLOB IMGUI_SOURCEFILES ${IMGUI_DIR}/*.cpp)
add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(${PROJECT_INCLUDE_DIR} ${PROJECT_DEPENDENCY_DIR} ${PROJECT_DEPENDENCY_DIR}/Bullet/src/ ${PROJECT_DEPENDENCY_DIR}/IMGUI ${PROJECT_DEPENDENCY_DIR}/GLAD ${PROJECT_INCLUDE_DIR}/InternalComponents ${PROJECT_INCLUDE_DIR}/Utilities)

set(PROJECT_SOURCES 
					${IMGUI_SOURCEFILES}
					"${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
					"${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
					"${PROJECT_SOURCES_DIR}/Main.cpp"
					"${PROJECT_DEPENDENCY_DIR}/GLAD/glad.c"
					"${PROJECT_SOURCES_DIR}/Component.cpp" 
					"${PROJECT_SOURCES_DIR}/GameObject.cpp" 
					"${PROJECT_SOURCES_DIR}/Transform.cpp" 
					"${PROJECT_INCLUDE_DIR}/GameObject.h" 
					"${PROJECT_SOURCES_DIR}/Vector3.cpp"
 "src/InternalComponents/MeshRenderer.cpp" "src/Texture.cpp" "src/Mesh.cpp" "src/Shader.cpp" "src/Scene.cpp" "src/InternalComponents/Camera.cpp" "src/Utilities/FileReader.cpp" "src/Engine.cpp" "src/Utilities/MeshFactory.cpp" "src/InternalComponents/Rigidbody.cpp" "src/HTime.cpp" "src/Input.cpp"  "src/InternalComponents/TestComponent.cpp" "src/InternalComponents/BoxCollider.cpp" "src/InternalComponents/PlaneCollider.cpp" "src/InternalComponents/Collider.cpp" "src/Physics.cpp" "src/Quaternion.cpp" "src/GUI.cpp" "src/Utilities/TextureLoader.cpp")

add_executable (Engine ${PROJECT_SOURCES})
set_target_properties(Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXECUTABLE_DIR})

if(WIN32)
	set(GLFW_LIBRARY_DIR "${PROJECT_DEPENDENCY_DIR}/GLFW/lib-vc2022/glfw3.lib")
	set(NETWORKING_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/Networking.lib")

	# if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	# 	set(LIBS 
	# 		"${BULLET_LIBRARY_DIR}/Debug/BulletCollision_Debug.lib" 
	# 		"${BULLET_LIBRARY_DIR}/Debug/BulletDynamics_Debug.lib" 
	# 		"${BULLET_LIBRARY_DIR}/Debug/LinearMath_Debug.lib" 
	# 		${GLFW_LIBRARY_DIR}
	# 		${NETWORKING_LIBRARY_DIR}
	# 	)
	# elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	# 	set(LIBS 
	# 		"${BULLET_LIBRARY_DIR}/Release/BulletCollision.lib" 
	# 		"${BULLET_LIBRARY_DIR}/Release/BulletDynamics.lib" 
	# 		"${BULLET_LIBRARY_DIR}/Release/LinearMath.lib" 
	# 		${GLFW_LIBRARY_DIR}
	# 		${NETWORKING_LIBRARY_DIR}
	# 	)
	# endif()
	set(LIBS
		set(GLFW_LIBRARY_DIR "${PROJECT_DEPENDENCY_DIR}/GLFW/build/src/libglfw3.a")
		set(NETWORKING_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/libNetworking.a")
		"${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Bullet/build/bin/BulletCollision/libBulletCollision.a"
		"${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Bullet/build/bin/BulletDynamics/libBulletDynamics.a"
		"${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Bullet/build/bin/LinearMath/libLinearMath.a"
		${GLFW_LIBRARY_DIR}
		${NETWORKING_LIBRARY_DIR}
	)
else()
	set(GLFW_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/GLFW/build/src/libglfw3.a")
	set(NETWORKING_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../lib/libNetworking.a")

	set(LIBS
		"${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/Bullet/build/src/BulletCollision/libBulletCollision.a"
		"${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/Bullet/build/src/BulletDynamics/libBulletDynamics.a"
		"${CMAKE_CURRENT_SOURCE_DIR}/../Dependencies/Bullet/build/src/LinearMath/libLinearMath.a"
		${GLFW_LIBRARY_DIR}
		${NETWORKING_LIBRARY_DIR}
	)
endif()

add_library(combined INTERFACE)
target_link_libraries(combined INTERFACE BulletCollision BulletDynamics LinearMath glfw ${NETWORKING_LIBRARY_DIR})
target_link_libraries(Engine BulletCollision BulletDynamics LinearMath glfw Networking)
