# LibFoo

Example of a library containing two libraries, `bar` and `baz` with `bar` dependent of `baz`.
`bar` is built as a static library, while `baz` as a shared library.

When the library is used as third party, if the code depends only on `bar` the 
dependency on `baz` is automatically managed by CMake. For example, if `bar` is
built as a static library, the dependency on `baz` is automatically added at linking
time.
