# CppML Documentation

#### Table of Contents

* [Installation](#installation)
* [Tutorial](#tutorial)
* [CppML Reference](#cppml-reference)
  * [Structure](#structure)
* [License](#license)

## Installation

[CppML](https://github.com/ZigaSajovic/CppML) can be installed in two ways. You can [install it using cmake](./installation/index.md#installing-using-cmake) as an `INTERFACE` library, or you can [embed it in your project](./installation/index.md#project-embedding) (e.g. via `git submodules` or *direct-copy*).

You may follow the [installation guide](./installation/index.md) for your convenience.

## Tutorial

`CppML` is a metalanguage for `C++`. It was designed to **simplify** the process of **creating** intricate **classes**, by letting the programmer **design** them through **expressions** that feel like **algorithms** in a **functional language**. It strives to be **easy** to **write** and **easy** to **read**, while being **efficient**. It does so by providing [`compositional pipelines`](./tutorial/index#pipes) through which [`parameter packs`](./tutorial/index#parameter-pack) can flow **without instantiating** new **types**.

You can follow the [`Metaprogramming Tutorial`](./tutorial/index.md) and learn how you can bring *elegant one-liners* to your class design.

## CppML Reference

[CppML](https://github.com/ZigaSajovic/CppML) comes with a detailed [`CppML reference`](./reference/index.md). Each construct provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use. The constructs are divided in the following headers:

| Header                                            | Description                                                                                                                                         |
|---------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------|
| [`Algorithm`](./reference/index.md#algorithm)     | Algorithms over parameter packs (e.g. [`Sort`](./reference/Algorithm/Sort.md), [`ZipWith`](./reference/Algorithm/ZipWith.md), etc.)                 |
| [`Arithmetic`](./reference/index.md#arithmetic)   | Arithmetic operations on type-values (e.g. [`Greater`](./reference/Arithmetic/Greater.md), [`Not`](./reference/Arithmetic/Not.md), etc.)            |
| [`Functional`](./reference/index.md#functional)   | Manipulation of metafunctions (e.g. [`Curry`](./reference/Functional/Curry.md), [`Map`](./reference/Functional/Map.md), etc.)                       |
| [`Pack`](./reference/index.md#pack)               | Manipulation of parameter packs (e.g. [`Drop`](./reference/Pack/Drop.md), [`Get`](./reference/Pack/Get.md), etc.)                                   |
| [`TypeTraits`](./reference/index.md#typetraits)   | Insights into types (e.g. [`IsSame`](./reference/TypeTraits/IsSame.md), [`IsClass`](./reference/TypeTraits/IsClass.md), etc.)                       |
| [`Vocabulary`](./reference/index.md#vocabulary)   | Vocabulary types of `CppML`   (e.g. [`ListT`](./reference/Vocabulary/ListT.md), [`Value`](./reference/Vocabulary/Value.md), etc.)                   |

The complete `CppML reference` can be found [here](./reference/index.md).

### Structure

CppML is structured as follows:
* each section has an associated header `.hpp` and a directory of the same name in the `CppML/` directory. For example, the `Algorithm` section has an `Algorithm.hpp` header located in the `include/CppML`
* every component of each section has a dedicated `.hpp` header inside the libraries associated directory. For example, `Sort`, a component of the `Algorithm` section, has a header located at `include/CppML/Algorithm/Sort.hpp`.

Thus, to use any component, you can either include its specific header (e.g. `#include <CppML/Algorithm/Sort.hpp>`), or include its containing header `#include <CppML/Algorithm.hpp>`. Note that you may include all of them at once using `#include <CppML/CppML.hpp>`.



## License

`CppML` in distributed under the **MIT License**. Please see the accompanying [`LICENSE`](../LICENSE) in the root of the project.
