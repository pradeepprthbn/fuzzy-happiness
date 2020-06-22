cmake_minimum_required(VERSION 3.18)

# set the project name
project(Boost)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

link_libraries(ws2_32 wsock32)

find_package(Boost 1.73.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  # add the executable
  add_executable(Server Server.cpp)
  add_executable(Client Client.cpp)
endif()