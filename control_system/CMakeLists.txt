cmake_minimum_required(VERSION 3.23)

project(control_system)

set(net_client_h "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/src/client")
set(net_client_p "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/build/libnet_client.dll")

set(net_server_h "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/src/server")
set(net_server_p "C:/Users/JAD-D/Documents/programs/cxx/testTask/net/build/libnet_server.dll")

include_directories(${net_client_h} ${net_server_h})

add_executable(control_system
	src/control_system/control_system.cpp
	src/main.cpp
)

if(WIN32)
  target_link_libraries(control_system ${net_client_p} ${net_server_p} wsock32 ws2_32 )
endif()
