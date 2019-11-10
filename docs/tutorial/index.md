# Tutorial

#### Table of Contents

* [`Key concepts`](#key-concepts)
  * [`Parameter pack`](#parameter-pack)
  * [`Pipe`](#pipe)
  * [`Metafunction`](#metafunction)
    * [`Metafunction type`](#metafunction-type)
    * [`Default pipes`](#default-pipes)
  * [`Metaprogramming in CppML`](#metaprogramming-in-cppml)
    * [`Invoking metafunctions`](#invoking-metafunctions)



## Key Concepts

### Parameter pack

> In the language of [CppML](https://github.com/ZigaSajovic/CppML), [`parameter packs`](#parameter-pack) are **streams** of **types passing** through **compositional pipes** of **transformations**.

A parameter pack is a template argument with the syntax

```c++
template <typename ...Pack>
```

You can never *hold* a parameter pack, i.e.
```c++
template <typename ...Pack>
using T = Pack;
```
is a nonsensical statement, that will not compile. You can only operate on them, and pass (expand) them into another template.
```c++
template <typename ...Pack>
using T = AnotherTemplate::f<Transform::f<Pack>...>;
```

This mechanic is at the core of [CppML](https://github.com/ZigaSajovic/CppML). [`Metafunctions`](#metafunction) take in (through their `f` alias) a parameter pack, transform it, and pass it on to another template through a `Pipe`.

**NOTE**

In the context of [CppML](https://github.com/ZigaSajovic/CppML), we can view

```c++
template<typename T, typename U>
```

as [`parameter packs`](#parameter-pack) of *non-variadic* length, and

```c++
template<typename T, typename ...Ts>
```
as *variadic* [`parameter packs`](#parameter-pack) with minimal length. For a justification, please see.

### Pipe

One of the pillars of [CppML](https://github.com/ZigaSajovic/CppML) is composability. As such, the ability to chain transformations on [`parameter packs`](#parameter-pack) is a core feature of the language. Concretely, every [`metafunction`](#metafunction) template has, as their last template parameter, a `Pipe` into which it passes the transformed parameter pack. Please see the [`metafunction`](#metafunction) section for a more in-depth explanation.

The reader might be familiar with the concept of pipes from bash ([`operator |`](https://stackoverflow.com/questions/9834086/what-is-a-simple-explanation-for-how-pipes-work-in-bash)), or from R ([`operator %>%`](https://www.rdocumentation.org/packages/pipeR/versions/0.6.1.3/topics/Pipe)), or from Haskel ([`operator >->`](http://hackage.haskell.org/package/pipes)).

### Metafunction

In [CppML](https://github.com/ZigaSajovic/CppML), a `metafunction` is a *template struct* with a *template alias* `f`. All `metafunctions` define, as their last template parameter, a metafunction [`Pipe`](#pipe) into which `f` will pass the transformed [`parameter pack`](#parameter-pack). In *pseudo-c++* this roughly translates into

```c++
template <typename PossibleArgs...,                                // zero of more arguments
          typename Pipe = (default: ml::Identity or ml::ToList)>   // see `Default pipes` below
struct MetaFunction {
  template <typename... Args>
  using f = Pipe::f<                                               // result passed to Pipe
                    mfImplementation::f<
                                        PossibleArgs...,
                                        Args...>...>;
};
```

#### Metafunction type

Throughout the [`CppML reference`](../reference/index.md), we use the following notation
```c++
f:: Args... -> Us... >-> Pipe
```
to mean:
> The template alias `::f` of Metafunction takes a parameter pack `Args...` and transforms it to a parameter pack `Us...` which is than passed on into `Pipe` (i.e. the `::f` alias of `Pipe` is invoked on `Us...`).

#### Default pipes

Metafunctions that pass on a single parameter `T` have `Pipe` defaulted to [`ml::Identity`](../reference/Functional/Identity.md), which is a metafunction with an alias `f`,
```c++
f:: T -> T
```
that simply returns the argument it was given.

Metafunctions that pass on parameter packs have `Pipe` defaulted to [`ml::ToList`](../reference/Functional/ToList.md), which is a metafunction with an alias `f`,
```c++
f:: Ts... -> ml::ListT<Ts...>
```
that wraps the parameter pack in an [`ml::ListT`](../reference/Vocabulary/List.md).

## Metaprogramming in `CppML`

### Invoking [`metafunctions`](#metafunction)

Due to the syntax of *c++*, unaided invocations of [`metafunctions`](#metafunction) look like

```c++
using T0 = typename MetaFunction::template f<int, string, char, vector<int>>;
```
As this is cumbersome, [CppML](https://github.com/ZigaSajovic/CppML) defines [`ml::f`](../reference/Functional/Invoke.md),
```c++
namespace ml {
template <typename Metafunction, typename ...Args>
using f = typename Metafunction::template f<Args...>;
}
```
an `alias` which invokes the metafunctions' `f` alias on the supplied arguments. Using it, `T0` (above) is equivalent to a more concise
```c++
using T1 = ml::f<MetaFunction, int, string, char, vector<int>>;
```

Taking a concrete example, we [`ml::Filter`](../reference/Algorithm/Filter.md) a parameter pack given a predicate [`ml::IsClass`](../reference/TypeTraits/IsClass.md)

```c++
using T2 = ml::f<ml::Filter<ml::IsClass<>>, int, string, char, vector<int>>;
static_assert(
          std::is_same_v<
                         T2,
                         ml::ListT<
                                   string, vector<int>>>);
```

#### Pack expansions and non-pack parameter of alias template

[CppML](https://github.com/ZigaSajovic/CppML) **correctly** handles **mixed** alias templates of **pack** and **non-pack** arguments. This means that you can create [`metafunctions`](#metafunction) from aliases (using the [`ml::F`](../reference/Functional/F.md), from the [`Functional`](../reference/index.md#functional) header) such as
```c++
template<typename T, typename U>
using AT1 = /*...*/
using MetaF1 = ml::F<AT1>;
```
and
```c++
template<typename T, typename ...Ts>
using AT2 = /*...*/
using MetaF2 = ml::F<AT2>;
```
and **they will properly interact** with the entire [CppML](https://github.com/ZigaSajovic/CppML) language, **without raising** the dreaded

> **error**: pack expansion used as argument for non-pack parameter of alias template

**We can hence view aliases like `AT1` as [`parameter packs`](#parameter-pack) of *non-variadic* length, and aliases like `AT2` as *variadic* [`parameter packs`](#parameter-pack) with minimal length.**
