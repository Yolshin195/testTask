cmake_minimum_required(VERSION 3.23)

project(test_task)

add_executable(control_system
  src/net/client/client.cpp
  src/net/server/server.cpp
	src/control_system.cpp
)

if(WIN32)
  target_link_libraries(control_system wsock32 ws2_32 )
endif()

add_executable(math_model
  src/net/client/client.cpp
  src/net/server/server.cpp
	src/math_model.cpp
)

if(WIN32)
  target_link_libraries(math_model wsock32 ws2_32 )
endif()

add_executable(logger
  src/net/server/server.cpp
	src/logger.cpp
)

if(WIN32)
  target_link_libraries(logger wsock32 ws2_32 )
endif()
