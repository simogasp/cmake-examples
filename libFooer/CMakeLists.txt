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

####
# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(Fooer VERSION 3.2.1)

if(TARGET bar)
  add_library(Foo::bar ALIAS bar)
else()
  # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
  # to avoid searching in temporary build directory of Foo project
  # See 5:
  #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
  find_package(Foo CONFIG REQUIRED)
endif()

####
# Create targets
add_library(fooer SHARED "src/fooer/Fooer.cpp" "src/fooer/Fooer.hpp")

####
# Properties of targets

option(FOOER_BAR_DEBUG "Compile with debug" ON)

if(CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "release")
  set(FOOER_BAR_DEBUG OFF CACHE BOOL "Compile with debug" FORCE)
else()
  # this is needed to avoid cache problems that requires to remove CMakeCache
  set(FOOER_BAR_DEBUG ON CACHE BOOL "Compile with debug" FORCE)
endif()


# Generate:
#   * ${CMAKE_CURRENT_BINARY_DIR}/fooer_export.h with BAR_EXPORT
include(GenerateExportHeader)
generate_export_header(fooer)

configure_file("cmake/fooer_config.hpp.in" fooer_config.hpp @ONLY)

# Global includes. Used by all targets
# Note:
#   * header location in project: Foo/Source/foo/Bar.hpp
#   * header can be included by C++ code `#include <foo/Bar.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/bar_export.hpp
#   * header can be included by: `#include <bar_export.hpp>`
target_include_directories(
    fooer PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

# Link required library
target_link_libraries(fooer PUBLIC Foo::bar)

####
# Installation (https://github.com/forexample/package-example)

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * header location after install: <prefix>/include/fooer/Fooer.hpp
#   * headers can be included by C++ code `#include <fooer/Fooer.hpp>`
install(
    TARGETS fooer
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
install(
    DIRECTORY "src/fooer"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.hpp"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/fooer_export.h -> <prefix>/include/fooer_export.h
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/fooer_export.h"
    DESTINATION "${include_install_dir}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/fooer_config.hpp"
    DESTINATION "${include_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Fooer/FooerConfig.cmake
#   * <prefix>/lib/cmake/Fooer/FooerConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Fooer/FooerTargets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
