cmake_minimum_required(VERSION 3.0)
project(Booer)

if(TARGET fooer)
  add_library(Fooer::fooer ALIAS fooer)
else()
  # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
  # to avoid searching in temporary build directory of Foo project
  # See 5:
  #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
  find_package(Fooer CONFIG REQUIRED)
endif()

# if(TARGET bar)
#   add_library(Foo::bar ALIAS bar)
# else()
#   # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
#   # to avoid searching in temporary build directory of Foo project
#   # See 5:
#   #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
#   find_package(Foo CONFIG REQUIRED)
# endif()

add_executable(booer booer.cpp)

target_link_libraries(booer Fooer::fooer)

# CMAKE_<CONFIG>_POSTFIX has no effect on executable
# * http://www.cmake.org/Bug/view.php?id=7868
set_target_properties(booer PROPERTIES DEBUG_POSTFIX "d")

enable_testing()
add_test(NAME BooerTest COMMAND booer)

install(TARGETS booer DESTINATION bin)
