# libBoostFooer - Example of multiple dependencies

LibBoostFooer depends PUBLICLY on `libFooer`, and PRIVATELY on Boost

Also this example explores the possibility of building the needed dependencies 
(`libFooer` and `libFoo`) if they are not found. A `3rdparty` directory contains 
the symlinks to the two directories. If `libFooer` is not found or provided, 
it will be built along with `libFoo`, and installed together with libBoostFooer.

## CMake features on show

* How to deal with existing targets for the dependencies, if the target already exists 
because it has been built previously (e.g. monolithic build) it can be renamed 
with an alias to match the name when imported. If the dependency does not exist,
then it must be found using `find_package()`.

