cmake_minimum_required(VERSION 3.23)

add_executable(client
	src/main_client.cpp
)

if(WIN32)
  target_link_libraries(client wsock32 ws2_32)
endif()

add_executable(server
	src/main_server.cpp
)

if(WIN32)
  target_link_libraries(server wsock32 ws2_32)
endif()