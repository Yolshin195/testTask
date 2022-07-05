cmake_minimum_required(VERSION 3.23)

project(control_system)

set(net_client "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/src/client")
include_directories(${net_client})

add_executable(control_system
	${net_client}/client.cpp
	src/control_system/control_system.hpp
	src/control_system/control_system.cpp
	src/main.cpp
)

if(WIN32)
  target_link_libraries(control_system wsock32 ws2_32)
endif()