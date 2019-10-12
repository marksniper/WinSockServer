cmake_minimum_required(VERSION 3.15)
project(WinSockServer)

set(CMAKE_C_STANDARD 99)

add_executable(WinSockServer server.c)
target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)