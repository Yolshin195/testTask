cmake_minimum_required(VERSION 3.23)

add_library(net_client SHARED
  src/client/client.cpp
)

if(WIN32)
  target_link_libraries(net_client wsock32 ws2_32)
endif()

add_library(net_server SHARED
  src/server/server.cpp
)

if(WIN32)
  target_link_libraries(net_server wsock32 ws2_32)
endif()
