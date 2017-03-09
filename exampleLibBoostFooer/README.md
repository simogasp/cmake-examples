# Example of Application using libBoostFooer

This is just an example on how to write a CMake for an application using libBoostFooer,
showing that the secondary dependency on `libFoo` is correctly propagated as well as
the private dependency on Boost.

## CMake features on show

* How to deal with existing targets for the dependencies, if the target already exists 
because it has been built previously (e.g. monolithic build) it can be renamed 
with an alias to match the name when imported. If the dependency does not exist,
then it must be found using `find_package()`.
