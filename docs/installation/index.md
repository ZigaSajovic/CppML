# Installation guide

[CppML](https://github.com/ZigaSajovic/CppML) can be installed in two ways. You can [install it using cmake](./installation/index.md#installing-using-cmake) as an `INTERFACE` library, or you can [embed it in your project](./installation/index.md#project-embedding) (e.g. via `git submodules` or *direct-copy*).

**NOTE**: as [CppML](https://github.com/ZigaSajovic/CppML) is a header only library, you can also simply copy the `include/` directory to the path of your project.

### Installing using cmake

[CppML](https://github.com/ZigaSajovic/CppML) is available as a CMake `INTERFACE` library. To install using cmake, clone the repository and execute the following commands from within the cloned folder.

```bash
git clone https://github.com/ZigaSajovic/CppML; cd CppML
mkdir build && cd build
cmake ..
make install
```

Consider running the build/install command with setting the install prefix, if you do not want to install [CppML](https://github.com/ZigaSajovic/CppML) system wide

```bash
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=${HOME}/CppML-install
```

#### Usage

To use the installed library in your project, add the following two lines to your `CMakeLists.txt`.

```cmake
find_package(CppML REQUIRED)
target_link_libraries(my_project CppML::CppML)
```

### Project Embedding

You can embed the entire [CppML](https://github.com/ZigaSajovic/CppML) source tree into your project's source tree (e.g. via `git submodules`, or copying the [CppML](https://github.com/ZigaSajovic/CppML) directory to the root of your project).

#### Usage

To use the installed library in your project, add the following two lines to your `CMakeLists.txt`.

```cmake
add_subdirectory(CppML)
target_link_libraries(my_project CppML::CppML)
```
