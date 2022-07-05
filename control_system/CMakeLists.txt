cmake_minimum_required(VERSION 3.23)

project(control_system)

add_executable(control_system
	src/control_system/control_system.hpp
	src/control_system/control_system.cpp
	src/main.cpp
)

if(WIN32)
  target_link_libraries(control_system wsock32 ws2_32)
endif()