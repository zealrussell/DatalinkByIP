cmake_minimum_required(VERSION 0.10)
project(DatalinkByIp_SERVER)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

# set(Boost_INCLUDE_DIR /home/muhammed/boost_1_68_0/)


set(APP_SERVER ../server)
set(APP_UTIL ../utils)
set(APP_PACKET ../transport_packet)
set(APP_PROTOCOL ../transport_protocols)
set(APP_CONSTANTS ../constants)
# set(APP_SERVER ../server_controller)


#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

include_directories(${APP_SERVER})
include_directories(${APP_UTIL})
include_directories(${APP_PACKET})
include_directories(${APP_PROTOCOL})
include_directories(${APP_CONSTANTS})


file(GLOB_RECURSE SRC_FILES ${APP_UTIL}/* ${APP_PACKET}/* ${APP_PROTOCOL}/*
        ${APP_CONSTANTS}/* ${APP_SERVER}/*)

add_executable(server.out
        ../main/server.cpp
        ${SRC_FILES})
