cmake_minimum_required (VERSION 3.8)

cmake_policy(SET CMP0091 NEW)
project (Engine)
SET(CMAKE_CXX_STANDARD 20)

set(DEPENDENCY_DIR "./Dependencies")
set(NETWORKING_INCLUDE_DIR "./Networking/include")
set(SHEILA_INCLUDE_DIR "./Dependencies/Sheila/Client/include" "./Dependencies/Sheila/Common/include" "./Dependencies/Sheila/Dependencies/ASIO/asio/include")

include_directories(${NETWORKING_INCLUDE_DIR} ${DEPENDENCY_DIR}/Bullet/src ${DEPENDENCY_DIR}/ASIO/asio/include ${SHEILA_INCLUDE_DIR})

add_subdirectory ("Networking" EXCLUDE_FROM_ALL)
add_subdirectory ("Core")
#add_subdirectory ("Server" EXCLUDE_FROM_ALL)

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Core)
