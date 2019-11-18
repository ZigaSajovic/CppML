# CppML Documentation

A Meta Language for C++

`CppML` is a metalanguage for `C++`. It was designed to simplify the process of creating intricate classes, by letting the programmer design them through expressions that feel like algorithms in a functional language. It strives to be easy to write and easy to read, while being efficient. It does so by providing [`compositional pipelines`](./tutorial/index.md#pipe) through which [`parameter packs`](./tutorial/index.md#parameter-pack) can flow without instantiating new types. Our goal is to give library developers programmatic control over the creation of class hierarchies with metaprograms that shape their structure and behaviour through metafunctional logic. This way constructions of complex designs are easily encoded in **concise** and **readable** functional **expressions**.

#### Table of Contents

* [Installation](#installation)
* [Tutorial](#tutorial)
* [CppML Reference](#cppml-reference)
  * [Structure](#structure)
* [Testing](#testing)
* [License](#license)

## Installation

[CppML](https://github.com/ZigaSajovic/CppML) can be installed in two ways. You can [`install it using cmake`](./installation/index.md#installing-using-cmake) as an `INTERFACE` library, or you can [`embed it in your project`](./installation/index.md#project-embedding) (e.g. via `git submodules` or *direct-copy*).

You may follow the [`Installation Guide`](./installation/index.md) for your convenience.

## Tutorial

`CppML` provides an in-depth [`Tutorial of the CppML language`](./tutorial/index.md) and its libraries.

---
#### Abstract

In this tutorial, we will go over the design of the `CppML` language and explore its prominent features in depth. You will learn about [`compositional pipelines`](./tutorial/index.md#pipe) and the flow of [`parameter packs`](./tutorial/index.md#parameter-pack) through them. You will learn about the structure of [`metafunctions`](./tutorial/index.md#metafunction), how to understand their [`metafunction type`](./tutorial/index.md#metafunction-type), and how they [`integrate with pipelines`](./tutorial/index.md#using-pipes).
You will learn how to [`manipulate metafunctions`](./tutorial/index.md#manipulating-metafunctions) using concepts like [`Currying`](./tutorial/index.md#currying), [`Product Maps`](./tutorial/index.md#product-map) and [`Branch Pipes`](./tutorial/index.md#functional-branching), and how to compose them into algorithms that will build your class designs.

Interspersed throughout the tutorial are *use-cases*, where we will formulate a problem and break down its solution into steps, and than translate them into `CppML`. Through them you will learn how to encode construction of (increasingly) complex designs into  **concise** and **readable** functional **expressions**.

---

Please see the [`Tutorial of the CppML language`](./tutorial/index.md).

## CppML Reference

[CppML](https://github.com/ZigaSajovic/CppML) comes with a detailed [`CppML reference`](./reference/index.md). Each construct provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use. The constructs of `CppML` are divided in into several smaller libraries, which are described below:

| Library                                         | Description                                                                                                                              |
|-------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------|
| [`Algorithm`](./reference/index.md#algorithm)   | Algorithms over parameter packs (e.g. [`Sort`](./reference/Algorithm/Sort.md), [`ZipWith`](./reference/Algorithm/ZipWith.md), etc.)      |
| [`Arithmetic`](./reference/index.md#arithmetic) | Arithmetic operations on type-values (e.g. [`Greater`](./reference/Arithmetic/Greater.md), [`Not`](./reference/Arithmetic/Not.md), etc.) |
| [`Functional`](./reference/index.md#functional) | Manipulation of metafunctions (e.g. [`Curry`](./reference/Functional/Curry.md), [`Map`](./reference/Functional/Map.md), etc.)            |
| [`Pack`](./reference/index.md#pack)             | Manipulation of parameter packs (e.g. [`Drop`](./reference/Pack/Drop.md), [`Get`](./reference/Pack/Get.md), etc.)                        |
| [`TypeTraits`](./reference/index.md#typetraits) | Insights into types (e.g. [`IsSame`](./reference/TypeTraits/IsSame.md), [`IsClass`](./reference/TypeTraits/IsClass.md), etc.)            |
| [`Vocabulary`](./reference/index.md#vocabulary) | Vocabulary types of `CppML`   (e.g. [`ListT`](./reference/Vocabulary/ListT.md), [`Value`](./reference/Vocabulary/Value.md), etc.)        |

The complete `CppML reference` can be found [here](./reference/index.md).

### Structure

`CppML` is structured as follows:
* each library has an associated header `.hpp` and a directory of the same name in the `CppML/` directory. For example, the `Algorithm` library has an `Algorithm.hpp` header located in the `include/CppML`
* every component of each library has a dedicated `.hpp` header inside the libraries associated directory. For example, `Sort`, a component of the `Algorithm` library, has a header located at `include/CppML/Algorithm/Sort.hpp`.

Thus, to use any component, you can either include its specific header (e.g. `#include <CppML/Algorithm/Sort.hpp>`), or include its libraries header `#include <CppML/Algorithm.hpp>`. Note that you may include all libraries at once using `#include <CppML/CppML.hpp>`.

## Testing

`CppML` provides [`tests`](../../test) for each of its components, which are automatically built with [`Github Actions`](https://github.com/ZigaSajovic/CppML/actions?query=workflow%3ATests) on each push. Please see the [`Testing Guide`](./testing/index.md) for instructions on how to build them, and additional details.

## License

`CppML` is distributed under the **MIT License**. Please see the accompanying [`LICENSE`](../LICENSE) in the root of the project.
