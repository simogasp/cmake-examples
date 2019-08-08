# CMake examples

Some examples on how to create libraries with CMake and properly use them in other CMake projects using the `LIBRARYConfig.cmake` files. 

The examples are partially inspired and taken from this repository https://github.com/forexample/package-example

## Content

The repository contains some examples of libraries

* `libFoo` is a library composed of two dependent libraries, `bar` and `baz` , with `bar` depending on `baz`
* `libFooer` is a library depending of `libbar`
  * It shows how the dependencies are propagated through the LIBRARYConfig.cmake
* `libBoostFooer` is a library depending of `libFooer` and Boost
  * It shows how to include a library having a cmake config and a library which only provides a FindLIBRARY.cmake

Some examples on how to use the libraries:

* `exampleFoo` shows how to build an application using `libFoo`
* `exampleFooer` shows how to build an application using `libFooer`



## Build

The repository can be built either monolithically using the `CMakeLists.txt` in the root or by compiling and installing each library separately.

Continuous integration: 
 - [![Build Status](https://travis-ci.org/simogasp/cmake-examples.svg?branch=master)](https://travis-ci.org/simogasp/cmake-examples) master branch.
 - [![Build status](https://ci.appveyor.com/api/projects/status/do663fdgpmqdwpdm?svg=true)](https://ci.appveyor.com/project/simogasp/cmake-examples) master branch.
 - [![Build Status](https://dev.azure.com/simogasp/cmake-examples/_apis/build/status/simogasp.cmake-examples?branchName=master&jobName=Ubuntu_1604)](https://dev.azure.com/simogasp/cmake-examples/_build/latest?definitionId=1&branchName=master) Ubuntu 16.04
 - [![Build Status](https://dev.azure.com/simogasp/cmake-examples/_apis/build/status/simogasp.cmake-examples?branchName=master&jobName=macos_10_14)](https://dev.azure.com/simogasp/cmake-examples/_build/latest?definitionId=1&branchName=master) OSX 10.14
 - [![Build Status](https://dev.azure.com/simogasp/cmake-examples/_apis/build/status/simogasp.cmake-examples?branchName=master&jobName=Windows_VS2017_Hosted)](https://dev.azure.com/simogasp/cmake-examples/_build/latest?definitionId=1&branchName=master) Windows VS 2017
 - [![Build Status](https://dev.azure.com/simogasp/cmake-examples/_apis/build/status/simogasp.cmake-examples?branchName=master&jobName=Windows_VS2019_Hosted)](https://dev.azure.com/simogasp/cmake-examples/_build/latest?definitionId=1&branchName=master) Windows VS 2019

### Monolithic build

```bash
mkdir build
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="`pwd`/install"
make install
```

Note: with the monolithic build the dependencies are not found using the classic `find_package()` command but using the properties in the global scope.

### Modular build

In order to build each library or executable independently, you basically need to do the same as the monolithic build and add to the cmake command the path(s) where the `LIBRARYConfig.cmake` can be found for each first level dependency. For example for building `exampleFooer` you need to add `-DFooer_DIR` with the Fooer's install path:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="`pwd`/install" -DFooer_DIR=path/to/directory/containing/FooerConfig.cmake/
```

(or, alternatively you can use `-DCMAKE_PREFIX_PATH=path/to/directory/containing/AllConfig.cmake`) if you are installing all the examples in the same install directory.

Check the README of each example for more info.



## Commented example

Here is a commented example taken from  https://github.com/forexample/package-example explaining how to build `exampleFoo`.

### Install Foo

Install project `Foo` in `Debug` and `Release` variants (`Makefile` generator):
``` bash
> cmake -HFoo -B_builds/Foo-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEBUG_POSTFIX=d -DCMAKE_INSTALL_PREFIX="`pwd`/install"
> cmake --build _builds/Foo-debug --target install
...
Install the project...
-- Install configuration: "Debug"
-- Installing: /.../install/lib/libbard.a
-- Installing: /.../install/lib/libbazd.a
-- Installing: /.../install/include/foo
-- Installing: /.../install/include/foo/Bar.hpp
-- Installing: /.../install/include/foo/Baz.hpp
-- Installing: /.../install/include/bar_export.h
-- Installing: /.../install/include/baz_export.h
-- Installing: /.../install/lib/cmake/Foo/FooConfig.cmake
-- Installing: /.../install/lib/cmake/Foo/FooConfigVersion.cmake
-- Installing: /.../install/lib/cmake/Foo/FooTargets.cmake
-- Installing: /.../install/lib/cmake/Foo/FooTargets-debug.cmake
```

```bash
> cmake -HFoo -B_builds/Foo-release -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="`pwd`/install"
> cmake --build _builds/Foo-release --target install
...
Install the project...
-- Install configuration: "Release"
-- Installing: /.../install/lib/libbar.a
-- Installing: /.../install/lib/libbaz.a
-- Up-to-date: /.../install/include/foo
-- Up-to-date: /.../install/include/foo/Bar.hpp
-- Up-to-date: /.../install/include/foo/Baz.hpp
-- Installing: /.../install/include/bar_export.h
-- Installing: /.../install/include/baz_export.h
-- Installing: /.../install/lib/cmake/Foo/FooConfig.cmake
-- Installing: /.../install/lib/cmake/Foo/FooConfigVersion.cmake
-- Installing: /.../install/lib/cmake/Foo/FooTargets.cmake
-- Installing: /.../install/lib/cmake/Foo/FooTargets-release.cmake
```

Note that:
* library target `bar` for different build types has different names: `libbar.a` and `libbard.a`
* header files is equal for both variants
* cmake-config files `FooConfig.cmake`, `FooConfigVersion.cmake` and `FooTargets.cmake` is equal for both variants
* `FooTargets-release.cmake` set `Release` imported target properties, e.g. `IMPORTED_LOCATION_RELEASE`
* `FooTargets-debug.cmake` set `Debug` imported target properties, e.g. `IMPORTED_LOCATION_DEBUG`

### ExampleFoo (use installed Foo)

Easiest way to find and include `FooConfig.cmake` file is to set `CMAKE_INSTALL_PREFIX`:
```bash
> cmake -HBoo -B_builds/exampleFoo -DCMAKE_INSTALL_PREFIX="`pwd`/install"
```

Also `CMAKE_PREFIX_PATH` and `Foo_DIR` can be used (do not forget to **remove** `builds/Boo` directory
before every configure):

```bash
> cmake -HBoo -B_builds/exampleFoo -DCMAKE_PREFIX_PATH="`pwd`/install"
> cmake -HBoo -B_builds/exampleFoo -DFoo_DIR="`pwd`/install/lib/cmake/Foo"
```

`find_package` config-mode command will include `FooConfig.cmake` file and import new target `Foo::bar`:

```bash
> cat exampleFoo/CMakeLists.txt 
find_package(Foo CONFIG REQUIRED)
add_executable(boo boo.cpp)
target_link_libraries(boo Foo::bar)
```

Note that:
* definition `FOO_BAR_DEBUG` will be added automatically
* include directory for target `Foo::bar` will be added automatically
* in `Debug`-mode macro `FOO_BAR_DEBUG` will be `1` and linker will use `libbard.a` library
* in `Release`-mode macro `FOO_BAR_DEBUG` will be `0` and linker will use `libbar.a` library
* if `find_package` command specify library version then `FooConfigVersion.cmake` module will check compatibility:

```bash
> grep find_package Boo/CMakeLists.txt 
find_package(Foo 2.0 CONFIG REQUIRED)
> cmake -HBoo -B_builds/Boo -DCMAKE_INSTALL_PREFIX="`pwd`/install"
CMake Error at CMakeLists.txt:8 (find_package):
  Could not find a configuration file for package "Foo" that is compatible
  with requested version "2.0".

The following configuration files were considered but not accepted:

    /.../install/lib/cmake/Foo/FooConfig.cmake, version: 1.2.3
```

