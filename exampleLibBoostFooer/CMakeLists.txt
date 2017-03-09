cmake_minimum_required(VERSION 3.0)
project(ExampleBoostFooer)

if(TARGET boostFooer)
  add_library(BoostFooer::boostFooer ALIAS boostFooer)
else()
  # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
  # to avoid searching in temporary build directory of Foo project
  # See 5:
  #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
  find_package(BoostFooer CONFIG REQUIRED)
endif()

add_executable(boostFooerApp boostFooer.cpp)

target_link_libraries(boostFooerApp BoostFooer::boostFooer)

# CMAKE_<CONFIG>_POSTFIX has no effect on executable
# * http://www.cmake.org/Bug/view.php?id=7868
set_target_properties(boostFooerApp PROPERTIES DEBUG_POSTFIX "d")

install(TARGETS boostFooerApp DESTINATION bin)

