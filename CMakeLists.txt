cmake_minimum_required (VERSION 3.8)

project (Engine)
SET(CMAKE_CXX_STANDARD 20)

set(NETWORKING_INCLUDE_DIR "./Networking/include")
set(ASIO_INCLUDE_DIR "C:/SDK/asio-1.22.2/include")

include_directories(${NETWORKING_INCLUDE_DIR} ${ASIO_INCLUDE_DIR})

add_subdirectory ("Networking")
add_subdirectory ("Core")
add_subdirectory ("Server")

#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Core)
