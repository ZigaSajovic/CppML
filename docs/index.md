# CppML Documentation

#### Table of Contents

## Installation

[CppML](https://github.com/ZigaSajovic/CppML) can be installed in two ways. You can [install it using cmake](./installation/index.md#installing-using-cmake) as an `INTERFACE` library, or you can [embed it in your project](./installation/index.md#project-embedding) (e.g. via `git submodules` or *direct-copy*).

You may follow the [installation guide](./installation/index.md) for your convenience.

## Usage

...

## CppML Reference

[CppML](https://github.com/ZigaSajovic/CppML) comes with a detailed [`API reference`](./reference/index.md). Each construct provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use. The constructs are divided in the following headers:

* [`Algorithm`](./reference/index.md#algorithm)
  * *algorithms* that operate on *parameter packs*
* [`Arithmetic`](./reference/index.md#arithmetic)
  * *arithmetic* operations on *types*
* [`ControlFlow`](./reference/index.md#controlflow)
  * constructs that *control* the *flow* of a metaprogram (e.g. [`IfElse`](./reference/ControlFlow/IfElse.md))
* [`Functional`](./reference/index.md#functional)
  * *functional* utilities (e.g. [`Curry`](./reference/Functional/Curry.md), [`Map`](./reference/Functional/Map.md), [`ProductMap`](./reference/Functional/ProductMap.md), etc.)
* [`Pack`](./reference/index.md#pack)
  * manipulation of *parameter packs*
* [`TypeTraits`](./reference/index.md#typetraits)
  * metafunctions that *reason* about the input *types*
* [`Vocabulary`](./reference/index.md#vocabulary)
  * *vocabulary* constructs of **CppML**

The complete `CppML reference` can be found [here](./reference/index.md).

## License
