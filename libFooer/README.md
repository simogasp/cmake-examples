# libFooer - Example of secondary dependency

LibFooer depends PUBLICLY on `libbar`, hence when writing the `FooerConfig.cmake` we need to propagate the dependency.

Have a look to [Config.cmake.in](libFooer/cmake/Config.cmake.in) on how to use `find_dependency()`.

Also this example shows how to dynamically generate and install a `config.h` for the project with all the definitions used to compile the code. 
Have a look to [fooer_config.hpp.in](libFooer/cmake/fooer_config.hpp.in) to see the template of the configuration file and the use of `#cmakedefine`.

## CMake features on show

* How to generate and export a more advanced `<library>Config.cmake` propagating the public dependency.

* How to deal with existing targets for the dependencies, if the target already exists 
because it has been built previously (e.g. monolithic build) it can be renamed 
with an alias to match the name when imported. If the dependency does not exist,
then it must be found using `find_package()`.

* How to generate configure files from templates with `configure_file()`.