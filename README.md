# CppML

A Meta Language for C++

`CppML` is a metalanguage for `C++`. It was designed to **simplify** the process of **creating** intricate **classes**, by letting the programmer **design** them through **expressions** that feel like **algorithms** in a **functional language**. It strives to be **easy** to **write** and **easy** to **read**, while being **efficient**. It does so by providing [`compositional pipelines`](./docs/tutorial/index.md#pipe) through which [`parameter packs`](./docs/tutorial/index.md#parameter-pack) can flow **without instantiating** new **types**. Our goal is to **give** library developers **programmatic control** over the creation of **class hierarchies** with **metaprograms** that shape their **structure and behaviour** through **metafunctional logic**. This way constructions of **complex designs** are easily encoded in **elegant** and **concise** functional **expressions**.

## Getting Started

### Installation

`CppML` provides an [`Installation Guide`](./docs/installation/index.md) which will have you up and running in moments. To quickly install `CppML` as a cmake `INTERFACE` library, run

```bash
git clone https://github.com/ZigaSajovic/CppML; cd CppML
mkdir build && cd build
cmake ..
make install
```

Please see the [`Installation Guide`](./docs/installation/index.md) for additional details and options.

### Tutorial

`CppML` provides an in-depth [`Tutorial of the CppML language`](./docs/tutorial/index.md) and its libraries.

---
#### Abstract

In this tutorial, we will go over the design of the `CppML` language and explore its prominent features in depth. You will learn about [`compositional pipelines`](./docs/tutorial/index.md#pipe) and the flow of [`parameter packs`](./docs/tutorial/index.md#parameter-pack) through them. You will learn about the structure of [`metafunctions`](./docs/tutorial/index.md#metafunction), how to understand their [`metafunction type`](./docs/tutorial/index.md#metafunction-type), and how they [`integrate with pipelines`](./docs/tutorial/index.md#using-pipes).
You will learn how to [`manipulate metafunctions`](./docs/tutorial/index.md#manipulating-metafunctions) using concepts like [`Currying`](./docs/tutorial/index.md#currying), [`Product Maps`](./docs/tutorial/index.md#product-map) and [`Branch Pipes`](./docs/tutorial/index.m#functional-branching), and how to compose them into algorithms that will build your class designs.

Interspersed throughout the tutorial are *use-cases*, where we will formulate a problem and break down its solution into steps, and than translate them into `CppML`. Through them you will learn how to encode construction of (increasingly) complex designs into  **elegant** and **concise** functional **expressions**.

---

Please see the [`Tutorial of the CppML language`](./docs/tutorial/index.md).

### User Documentation

Complete [`User documentation`](./docs/index.md) can be found in the [`docs/`](./docs) directory.

### CppML Reference

[`CppML`](https://github.com/ZigaSajovic/CppML) comes with a detailed [`CppML reference`](./docs/reference/index.md). Each construct provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use. The constructs of `CppML` are divided in into several smaller libraries, which are described below:

| Library                                              | Description                                                                                                                                        |
|------------------------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------|
| [`Algorithm`](./docs/reference/index.md#algorithm)   | Algorithms over parameter packs (e.g. [`Sort`](./docs/reference/Algorithm/Sort.md), [`ZipWith`](./docs/reference/Algorithm/ZipWith.md), etc.)      |
| [`Arithmetic`](./docs/reference/index.md#arithmetic) | Arithmetic operations on type-values (e.g. [`Greater`](./docs/reference/Arithmetic/Greater.md), [`Not`](./docs/reference/Arithmetic/Not.md), etc.) |
| [`Functional`](./docs/reference/index.md#functional) | Manipulation of metafunctions (e.g. [`Curry`](./docs/reference/Functional/Curry.md), [`Map`](./docs/reference/Functional/Map.md), etc.)            |
| [`Pack`](./docs/reference/index.md#pack)             | Manipulation of parameter packs (e.g. [`Drop`](./docs/reference/Pack/Drop.md), [`Get`](./docs/reference/Pack/Get.md), etc.)                        |
| [`TypeTraits`](./docs/reference/index.md#typetraits) | Insights into types (e.g. [`IsSame`](./docs/reference/TypeTraits/IsSame.md), [`IsClass`](./docs/reference/TypeTraits/IsClass.md), etc.)            |
| [`Vocabulary`](./docs/reference/index.md#vocabulary) | Vocabulary types of `CppML`   (e.g. [`ListT`](./docs/reference/Vocabulary/ListT.md), [`Value`](./docs/reference/Vocabulary/Value.md), etc.)        |

The complete `CppML reference` can be found [here](./docs/reference/index.md).
