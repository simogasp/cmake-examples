cmake_minimum_required(VERSION 3.0)

set(LIBRARY_NAME "CppCheckerDemo")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD   11)

include_directories(${CMAKE_SOURCE_DIR})

file( GLOB SRCS src/*.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "^Android")
  add_library(${LIBRARY_NAME} SHARED ${SRCS})
  target_link_libraries(${LIBRARY_NAME} log android)
endif()