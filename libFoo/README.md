# LibFoo

Example of a library without dependencies containing two libraries, `bar` and `baz` 
with `bar` dependent of `baz`. `bar` is built as a static library, while `baz` as a shared library.

When the library is used as third party, if the code depends only on `bar`, the 
dependency on `baz` is automatically managed by CMake. For example, if `bar` is
built as a static library, the dependency on `baz` is automatically added at linking
time.

## CMake features on show

* How to add compile definition with `target_compile_definitions()`. Note that these
definition will be propagated in the exported library according to the given 
visibility (`PUBLIC`, `PRIVATE` and `INTERFACE`).

* How to include directories per target with `target_include_directories()` using 
generator expressions, so that the includes are different whether it is in tree 
building or as a 3rd party. 

* How to set properties with `set_target_properties()`, in particular for the 
`DEBUG_POSTFIX` which allows to append a postfix to the library when built in debug 
(typically, 'd'), and `VERSION` which allows to generate symlinks for the shared 
object containing the version numbers of the library (e.g. libfoo.1.2.so).

* How to automatically generate export headers with `generate_export_header()`.

* How to generate and export a basic `<library>Config.cmake` with `configure_package_config_file()`, 
`<library>Targets.cmake` and `<library>Versions.cmake`.