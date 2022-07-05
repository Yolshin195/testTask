cmake_minimum_required(VERSION 3.23)

project(logger)

set(net_server "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/src/server")
include_directories(${net_server})

add_executable(logger
	${net_server}/server.cpp
	src/logger_server/logger_server.hpp
	src/logger_server/logger_server.cpp
	src/main.cpp
)

if(WIN32)
  target_link_libraries(logger wsock32 ws2_32)
endif()
