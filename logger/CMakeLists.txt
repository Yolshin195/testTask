cmake_minimum_required(VERSION 3.23)

project(logger)

add_executable(logger
	src/logger_server/logger_server.hpp
	src/logger_server/logger_server.cpp
	src/main.cpp
)

if(WIN32)
  target_link_libraries(logger wsock32 ws2_32)
endif()
