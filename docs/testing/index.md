# Testing

`CppML` provides [`tests`](../../test) for each of its components, which are automatically built with [`Github Actions`](https://github.com/ZigaSajovic/CppML/actions?query=workflow%3ATests) on each push.

## About the tests

Because `CppML` is a metalanguage, all computations expressed in it happen at compile time. This means that all the tests are `static`, and if the they compile, they have been passed.

### Structure

The tests are located in the [`test/src`](../../test/src) directory, and follow the same structure as the [`include/CppML`](../reference/index.md):
* the tests for each library have an associated file `.cpp` and a directory of the same name in the `test/src/` directory. For example, the tests for the `Algorithm` library have an `Algorithm.cpp` file located in the `test/src`. 
* every component of each library has a dedicated `.hpp` test header inside the libraries associated test directory. For example, `Sort`, a component of the `Algorithm` library, has a header located at `test/src/Algorithm/Sort.hpp`.

Each library defines a target named `CppML_<LIBRARY>_TEST`, where `<LIBRARY`> is the name of library in question.

## Building the tests

To build the tests configure the project with `-DBUILD_TESTS=True`, which means:

```bash
mkdir build && cd build;
cmake .. -DBUILD_TESTS=True
make
```

If the build succeeds, the test have been passed.
