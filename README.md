# CppML

A Meta Language for C++

`CppML` is a metalanguage for `C++`. It was designed to **simplify** the process of **creating** intricate **classes**, by letting the programmer **design** them through **expressions** that feel like **algorithms** in a **functional language**. It strives to be **easy** to **write** and **easy** to **read**, while being **efficient**. It does so by providing [`compositional pipelines`](./docs/tutorial/index#pipes) through which [`parameter packs`](./docs/tutorial/index#parameter-pack) can flow **without instantiating** new **types**.

Our goal is to **give** library developers **programmatic control** over the creation of **class hierarchies** with **metaprograms** that shape their **structure and behaviour** through **metafunctional logic**.
This way constructions of **complex designs** are easily encoded in **elegant** and **concise** functional **expressions**.

### Getting Started

`CppML` provides detailed [`User documentation`](./docs/index.md), which you are invited explore. It provides an [`Installation Guide`](./docs/installation/index.md) which will have you up and running in moments. To quickly install `CppML` as a cmake `INTERFACE` library, run

```bash
git clone https://github.com/ZigaSajovic/CppML; cd CppML
mkdir build && cd build
cmake ..
make install
```

Please see the [`Installation Guide`](./docs/installation/index.md) for additional details and options.


## Tutorial



### User Documentation

Complete [`User documentation`](./docs/index.md) can be found in the [`docs/`](./docs) directory.

### CppML Reference

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
