# This file creates project 'Fooer' with s library target fooer.
#  After installation this project can be found
# by 'find_package(... CONFIG)' command:
#
#    find_package(Fooer CONFIG REQUIRED)
#    target_link_libraries(... Fooer::fooer)
#

####
# Set minimum version of CMake. Since command 'project' use
# VERSION sub-option we need 3.0.
cmake_minimum_required(VERSION 3.0)

set(LIBRARY_NAME "CppCheckerDemo")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD   11)

include_directories(${CMAKE_SOURCE_DIR})

# add_subdirectory(xhook)
if (CMAKE_SYSTEM_NAME MATCHES "^Android")
  add_library(${LIBRARY_NAME} SHARED     
    src/nulldemo.cpp    
    src/nulldemo2.cpp    
    )
  target_link_libraries(${LIBRARY_NAME} log android)
endif()