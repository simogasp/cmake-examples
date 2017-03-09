# This file creates project 'BoostFooer' with s library target boostFooer.
#  After installation this project can be found
# by 'find_package(... CONFIG)' command:
#
#    find_package(BoostFooer CONFIG REQUIRED)
#    target_link_libraries(... BoostFooer::boostFooer)
#

####
# Set minimum version of CMake. Since command 'project' use
# VERSION sub-option we need 3.0.
cmake_minimum_required(VERSION 3.0)

####
# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(BoostFooer VERSION 3.2.1)

if(TARGET fooer)
  # it means the target is already defined somewhere, typically when building
  # the whole project as a monolith
  add_library(Fooer::fooer ALIAS fooer)
  
  # this is needed for the propagation with the BoostFooerConfig.cmake: if we are in a
  # monolithic build, it means that the target fooer is being built with the current
  # target and it will be installed in the same location, ie ${CMAKE_INSTALL_PREFIX}
  # So define Fooer_DIR, if not the case, to point to that location, that way 
  # BoostFooerConfig.cmake will set it as well and it will propagate the dependency.
  if(NOT DEFINED Fooer_DIR)
    set(Fooer_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/Fooer")
  endif()
else()
  # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
  # to avoid searching in temporary build directory of Foo project
  # See 5:
  #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
  find_package(Fooer CONFIG QUIET)
  
  if(NOT Fooer_FOUND)
    # if not found add from tree
    set(Foo_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/Foo")
    set(Fooer_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/Fooer")
    add_subdirectory(src/3rdparty/libFoo)
    add_subdirectory(src/3rdparty/libFooer)
    add_library(Fooer::fooer ALIAS fooer)
  endif()
    
endif()

find_package(Boost REQUIRED COMPONENTS filesystem)

####
# Create targets
add_library(boostFooer STATIC "src/boostFooer/BoostFooer.cpp" "src/boostFooer/BoostFooer.hpp")

####
# Properties of targets

# Add definitions for targets
# Values:
#   * Debug: -DBOOSTERFOOER_DEBUG=1
#   * Release: -DBOOSTERFOOER_DEBUG=0
#   * other: -DBOOSTERFOOER_DEBUG=0
target_compile_definitions(boostFooer PUBLIC "BOOSTERFOOER_DEBUG=$<CONFIG:Debug>")
target_compile_definitions(boostFooer PRIVATE ${Boost_DEFINITIONS})


# Generate:
#   * ${CMAKE_CURRENT_BINARY_DIR}/boostFooer_export.h with BAR_EXPORT
include(GenerateExportHeader)
generate_export_header(boostFooer BASE_NAME "boost_fooer")

# Global includes. Used by all targets
# Note:
#   * header location in project: Foo/Source/foo/Bar.hpp
#   * header can be included by C++ code `#include <foo/Bar.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/bar_export.hpp
#   * header can be included by: `#include <bar_export.hpp>`
target_include_directories(
    boostFooer PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
    PRIVATE ${Boost_INCLUDE_DIRS}
)


# Link required library
target_link_libraries(boostFooer PUBLIC Fooer::fooer PRIVATE ${Boost_LIBRARIES})
set_target_properties(boostFooer PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(boostFooer PROPERTIES DEBUG_POSTFIX "d")
# allows to generate proper symlinks for shared libs
set_target_properties(boostFooer PROPERTIES VERSION ${PROJECT_VERSION})
#set_target_properties(boostFooer PROPERTIES CXX_STANDARD 11)
#target_compile_features(boostFooer PRIVATE cxx_range_for)

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
#   * header location after install: <prefix>/include/boostFooer/BoostFooer.hpp
#   * headers can be included by C++ code `#include <boostFooer/BoostFooer.hpp>`
install(
    TARGETS boostFooer
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
#   * Source/foo/Bar.hpp -> <prefix>/include/foo/Bar.hpp
install(
    DIRECTORY "src/boostFooer"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.hpp"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/boostFooer_export.h -> <prefix>/include/boostFooer_export.h
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/boost_fooer_export.h"
    DESTINATION "${include_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/BoostFooer/BoostFooerConfig.cmake
#   * <prefix>/lib/cmake/BoostFooer/BoostFooerConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/BoostFooer/BoostFooerTargets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)
