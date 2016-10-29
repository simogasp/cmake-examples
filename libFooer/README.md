# libFooer - Example of secondary dependency

LibFooer depends PUBLICLY on `libbar`, hence when writing the `FooerConfig.cmake` we need to propagate the dependency.

Have a look to [Config.cmake.in](libFooer/cmake/Config.cmake.in) on how to use `find_dependency()`.

Also this example shows how to dynamically generate and install a `config.h` for the project with all the definitions used to compile the code.
