cmake_minimum_required (VERSION 3.8)

project (Engine)
SET(CMAKE_CXX_STANDARD 20)

set(DEPENDENCY_DIR "./Dependencies")
set(NETWORKING_INCLUDE_DIR "./Networking/include")

include_directories(${NETWORKING_INCLUDE_DIR} ${DEPENDENCY_DIR}/Bullet/src ${DEPENDENCY_DIR}/ASIO/asio/include)

add_subdirectory ("Networking")
add_subdirectory ("Core")
add_subdirectory ("Server")

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Core)
