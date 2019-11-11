# `CppML` Tutorial

#### Table of Contents

* [`Introduction`](#introduction)
* [`Key concepts`](#key-concepts)
  * [`Parameter pack`](#parameter-pack)
  * [`Pipe`](#pipe)
  * [`Metafunction`](#metafunction)
    * [`Metafunction type`](#metafunction-type)
    * [`Default pipes`](#default-pipes)
    * [`Invoking metafunctions`](#invoking-metafunctions)
    * [`Using pipes`](#using-pipes)
  * [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions)
* [`Manipulating metafunctions`](#manipulating-metafunctions)
  * [`Composition`](#composition)
  * [`Product`](#product)
  * [`Product Map`](#product-map)
  * [`Partial evaluation`](#partial-evaluation)
    * [`Partial`](#partial)
    * [`PartialR`](#partialr)
    * [`Bind`](#bind)
    * [`Use case: A generator of linear CRTP class hierarchies`](#use-case-a-generator-of-linear-crtp-class-hierarchies)
  * [`Currying`](#currying)
    * [`Curry`](#curry)


## Introduction

`CppML` is a metalanguage for `C++`. It was designed to **simplify** the process of **creating** intricate **classes**, by letting the programmer **design** them through **expressions** that behave as **algorithms** in a **functional language**.

3 design principles

compositional pipelines

it strives to be easy to speak and easy to read



### Link to Reference

Throughout this tutorial, all links with the `ml::` prefix (e.g. [`ml::Map`](../reference/Functional/Map.md)) lead to the [`CppML reference`](../reference/index.md) for that specific metafunction. Each of them provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use.

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
as *variadic* [`parameter packs`](#parameter-pack) with minimal length. This is because [CppML](https://github.com/ZigaSajovic/CppML) **correctly** handles **mixed** alias templates of **pack** and **non-pack** arguments. 

### Pipe

One of the pillars of [CppML](https://github.com/ZigaSajovic/CppML) is composability. As such, the ability to chain transformations on [`parameter packs`](#parameter-pack) is a core feature of the language. Concretely, every [`metafunction`](#metafunction) template has, as their last template parameter, a `Pipe` into which it passes the transformed parameter pack. Please see the [`metafunction`](#metafunction) section for a more in-depth explanation.

The reader might be familiar with the concept of pipes from bash ([`operator |`](https://stackoverflow.com/questions/9834086/what-is-a-simple-explanation-for-how-pipes-work-in-bash)), or from R ([`operator %>%`](https://www.rdocumentation.org/packages/pipeR/versions/0.6.1.3/topics/Pipe)), or from Haskel ([`operator >->`](http://hackage.haskell.org/package/pipes)).

### Metafunction

In [CppML](https://github.com/ZigaSajovic/CppML), a `metafunction` is an instantiation of a *template struct* with a *template alias* `f`. All `metafunctions` define, as their last template parameter, a metafunction [`Pipe`](#pipe) into which `f` will pass the transformed [`parameter pack`](#parameter-pack). In *pseudo-c++* this roughly translates into

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

#### Invoking [`metafunctions`](#metafunction)

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

#### Using [`Pipes`](#pipe)

Suppose we want a metafunction that takes the elements of the [`parameter pack`](#parameter-pack) in the range `[2, 6]`, and from that range remove all ([`ml::RemoveIf`](../reference/Algorithm/Filter.md)) which are a class type ([`ml::IsClass`](../reference/TypeTraits/IsClass.md)).

```c++
using F = ml::Pivot<2,                                    // make third element the first
          /* Pipe*/ ml::Head<4,                           // take first 4 elements
          /* Pipe*/          ml::RemoveIf<ml::IsClass<>>; // filter them
```

See also [`ml::Pivot`](../reference/Algorithm/Pivot.md), and [`ml::Head`](../reference/Pack/Head.md) (defined in the [`Pack`](../reference/index.md#pack) header).

### Lifting templates to metafunctions

Any template, either a `struct` / `class`

```c++
template<typename ...Ts>
struct T { /* ... */};
```

or an `alias`

```c++
template<typename ...Ts>
using AT = /* .... */;
```
can be *lifted* to a [`metafunction`](#metafunction), through the use of [`ml::F`](../reference/Functional/F.md)`<Template, Pipe>` (see its [reference](../reference/Functional/F.md)). For example, we can make `std::tuple` a metafunction

```c++
using TupleF = ml::F<std::tuple>;
```

and alter the previous example, to [`Pipe`](#pipe) the result into it

```c++
using T2 = ml::f<
                 ml::Filter<                     // Filter
                            ml::IsClass<>,       // Predicate
                            TupleF>,             // Pipe of Filter
                int, string, char, vector<int>>;
static_assert(
          std::is_same_v<
                         T2,
                         std::tuple<
                                    string, vector<int>>>);
```

**NOTE**

Although both `T` and `AT` above have `variadic parameter packs`, the [`parameter packs`](#parameter-pack) can be of any form (as specified in the note [here](#parameter-pack)); i.e. `variadic`, `non-variadic` and `variadic with minimal length`. 

## Manipulating metafunctions

[CppML](https://github.com/ZigaSajovic/CppML) aims to be used and read as a (meta) functional language. As such, the key skill to master, is how to combine and compose **simple** [`metafunctions`](#metafunction) into **complex** [`metafunctions`](#metafunction).

### Composition

The most basic of manipulations of metafunctions is the composition. The idiomatic way to compose [`metafunctions`](#metafunction) when writing metaprograms is [using pipes](#using-pipes). The flow of composition looks like this.

```
f:: Ts ... -> Us... >-> Pipe
```

So, given that we have [`ml::IsClass`](../reference/TypeTraits/IsClass.md), and [`ml::Not`](../reference/TypeTraits/Not.md), we can define

```c++
using IsNotClass = ml::IsClass<ml::Not<>>;
```
`IsNotClass` by [using pipes](#using-pipes). But [using pipes](#using-pipes) is only possible, when you have access to setting the template parameters. To illustrate the point, suppose we have *concrete* metafunctions

```c++
using IsClassF = ml::IsClass<>;
using NotF = ml::Not<>;
```

for which we do not have access to [`Pipe`](#pipe). In these cases, we can use the [`ml::Compose`](../reference/Functional/Compose.md), and construct

```c++
using IsNotClassF = ml::Compose<NotF, IsClassF>;
```
which is equivalent to `IsNotClass` above. We can go further and make it an `alias` with a [`Pipe`](#pipe) template parameter,

```c++
template <typename Pipe = ml::Identity>
using IsNotClassF = ml::Compose<Pipe, NotF, IsClassF>;
```

making it a proper [`metafunction`](#metafunction). We can see that

```c++
static_assert(std::is_same_v<
                  ml::f<IsNotClassF<ml::Not<>>, int>
                  ml::f<ml::IsClass<>, int>>);
```
negating is `IsNotClassF` is equivalent to `IsClass`.

### Product

A different way to combine [`metafunctions`](#metafunction) is to take their [`ml::Product`](../reference/Functional/Product.md)`<Fs..., Pipe>`. An [`ml::Product`](../reference/Functional/Product.md)`<Fs..., Pipe>`, which takes `n` metafunctions `Fs...` (see [`ml::Product`](../reference/Functional/Product.md) for detailed reference), each mapping

```c++
f:: Ts... -> U
```
and a [`Pipe`](#pipe),
```c++
f:: Us... -> Vs...
```
is itself a metafunction
```c++
f:: Ts... -> Fs(Ts...)... >-> Pipe
             ^^^^^^^^^^^^
             U0...Uk...Un
```
which can be topologically envisioned as
```c++
              -> U0 -
            /    ...  \
f:: Ts ... -  ->  Uk -- >-> Pipe
            \    ...  /
              -> Un - 
```

where each arrow is one of the metafunctions `Fs...`.

To demonstrate, we implement a [`metafunction`](#metafunction) `partition`, which takes a `Predicate`, and partitions a [`parameter pack`](#parameter-pack) into two parts, one containing the elements that satisfy the `Predicate`, and one containing those two don't. This can be achieved by taking a [`ml::Product`](../reference/Functional/Product.md) of [`ml::Filter`](../reference/Algorithm/Filter.md) and [`ml::RemoveIf`](../reference/Algorithm/RemoveIf.md) (from the [`Algorithm`](../reference/index.md#algorithm) header).

```c++
template <typename Predicate, typename Pipe = ml::ToList>
using Partition = ml::Product<
                        ml::Filter<Predicate>,
                        ml::RemoveIf<Predicate>,
                        Pipe>;
```

To see how it works, we invoke it on `int, string, bool, vector<int>`.

```c++
using T = ml::f<
                Partition<ml::IsClass<>>,
                int, string, bool, vector<int>>;
static_assert(
      std::is_same_v<
          T,
          ml::ListT<
              ml::ListT<string, vector<int>>,
              ml::ListT<int, bool>>>);
```

**NOTE**

[CppML](https://github.com/ZigaSajovic/CppML) defines [`ml::Partition`](../reference/Algorithm/Partition.md) in the [`Algorithm`](../reference/index.md#algorithm) header. The implementation is almost identical to the one presented here.


### Product map

As another way to make a product of [`metafunctions`](#metafunction) is to take their [`ml::ProductMap`](../reference/Functional/ProductMap.md)`<Fs..., Pipe>`. An [`ml::ProductMap`](../reference/Functional/ProductMap.md)`<Fs..., Pipe>`, which takes `n` metafunctions `Fs...` (see [`ml::ProductMap`](../reference/Functional/ProductMap.md) for detailed reference), each mapping

```c++
f:: T -> U
```
and a [`Pipe`](#pipe),
```c++
f:: Us... -> Vs...
```
is itself a metafunction
```c++
f:: Ts... -> Fs(Ts)...  >-> Pipe
            ^^^^^^^^^^^^
            U0...Uk...Un
```
which can be topologically envisioned as

```
     T0 -> U0 -
    ... -> ...  \
f::  Tk -> Uk --  >-> Pipe
    ... -> ...  /
     Tn -> Uk -
      
```
where each arrow is one of the metafunctions `Fs...`.

To demonstrate we implement a [`metafunction`](#metafunction) that *counts* the number of elements of a [`parameter pack`](#parameter-pack) that satisfy a `Predicate`. We will do so by utilizing the [`ml::Reduce`](../reference/Algorithm/Reduce.md) (from the [`Algorithm`](../reference/index.md#algorithm) header). Looking at its [reference](../reference/Algorithm/Reduce.md), we see that it is instantiated with a metafunction

```c++
f:: Init, U -> Init'
```

that is used to accumulate the *generalized sum*. In our case, we want a metafunction that will add `1` to the current value if the predicate is `true` and `0` otherwise. This means

```c++
f:: Init, U -> Init, Predicate(U) >-> Add
```
which is equivalent to
```c++
f:: Init, U -> Identity(Init), Predicate(U) >-> Add
```
We now see that this is the [`ml::ProductMap`](../reference/Functional/ProductMap.md) of [`ml:Identity`](../reference/Functional/Identity.md) and the `Predicate`, which [`Pipe`](#pipe)s to [`ml::Add`](../reference/Arithmetic/Add.md). Hence

```c++
template<typename Predicate, typename Pipe = ml::Identity>
using CountIf_ = ml::Reduce<
                           ml::ProductMap<
                                          ml::Identity,
                                          Predicate,
                                          ml::Add<>>,
                          Pipe>;
```

To see how it works, we invoke it on `int, string, bool, vector<int>`.

```c++
using T = ml::f<
                CountIf_<ml::IsClass<>>,
                ml::Int<0>,                      // Init as first parameter for reduce
                int, string, bool, vector<int>>;
static_assert(
              std::is_same_v<
                            T,
                            ml::Int<2>>);
```
For `CountIf_` to fully be a `CountIf` metafunction, we need to get rid of the need to pass the `ml::Int<0>` as the initial value for [`ml::Reduce`](../reference/Algorithm/Reduce.md), because the count always starts at `0`. We can do this by [partially evaluating](#partial-evaluation) `CountIf_`, which is the subject of the next section.

**NOTE**

[CppML](https://github.com/ZigaSajovic/CppML) defines [`ml::CountIf`](../reference/Algorithm/CountIf.md) in the [`Algorithm`](../reference/index.md#algorithm) header.

### Partial evaluation

After studying how you can combine [`metafunctions`](#metafunction), we take a look at how we can transform a metafunction into a different metafunction, that has some of its parameters fixed.

#### Partial

To partially evaluate a [`metafunction`](#metafunction) from the left, we employ the [`ml::Partial`](../reference/Functional/Partial.md)`<F, Args...>` from the [`Functional`](../reference/index.md#functional) header.
`Partial<F, Args...>` is a metafunction, that is a partial evaluation of `F`. When invoked on `Ts...`, it is as if `F` was invoked on `Args..., Ts...`.

```c++
f:: Ts... -> F(Args..., Ts...)
```

Hence, we can use [`ml::Partial`](../reference/Functional/Partial.md) to partially evaluate `CountIf_` from the previous section on `ml::Int<0>`. Full implementation looks like this

```c++
template<typename Predicate, typename Pipe = ml::Identity>
using CountIf = ml::Partial<
                        ml::Reduce<
                           ml::ProductMap<
                                  ml::Identity,
                                  Predicate,
                                  ml::Add<>>,
                           Pipe>,
                        ml::Int<0>>;
```
To test it, we invoke it on the same example.
```c++
using T = ml::f<
                CountIf<ml::IsClass<>>,
                int, string, bool, vector<int>>;
static_assert(
              std::is_same_v<
                            T,
                            ml::Int<2>>);
```

#### PartialR

To partially evaluate a [`metafunction`](#metafunction) from the right, we employ the [`ml::PartialR`](../reference/Functional/PartialR.md)`<F, Args...>` from the [`Functional`](../reference/index.md#functional) header.
`PartialR<F, Args...>` is a metafunction, that is a partial evaluation of `F`. When invoked on `Ts...`, it is as if `F` was invoked on `Ts..., Args...`.

```c++
f:: Ts... -> F(Ts..., Args...)
```

#### Bind

To give user complete control over partial evaluations, [CppML](https://github.com/ZigaSajovic/CppML) provides [`ml::Bind`](../reference/Functional/Bind.md)`<F, `[`ml::Par<Is, Args>`](../reference/Functional/Bind.md)`...>` for the [`Functional`](../reference/index.md#functional) header. [`ml::Bind`](../reference/Functional/Bind.md)`<F, `[`ml::Par<Is, Args>`](../reference/Functional/Bind.md)`...>` is a partial evaluation, where each element on the parameter pack `Args...` is bound to its corresponding position `int ...Is`.

The [`ml::Par<I, T>`](../reference/Functional/Bind.md) is the parameter holder for [`ml::Bind`](../reference/Functional/Bind.md) (see its [reference page](../reference/Functional/Bind.md)). `Aliases` of the form

```c++
template <typename T>
using _0 = ml::Par<0, T>
```

are defined for `N` in the range `[0, 20]`.

To illustrate [`ml::Bind`](../reference/Functional/Bind.md)s functionality, we state that binding to first few positions

```c++
using boundF = ml::Bind<F, ml::_0<int>, ml::_1<bool>>;
```

is equivalent to partially evaluating from the left.

```c++
using boundF = ml::Partial<F, int, bool>;
```

Please consult its [reference page](../reference/Functional/Bind.md) for details and an example demonstration of use.

#### Use case: A generator of linear CRTP class hierarchies

As a use case, we will implement a metaprogram that generates a **linear [`CRTP`](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) class hiearchy** from a parameter pack of templates.

Suppose we define policy classes

```c++
template <class MostDerived, class BasePolicy>
struct Policy_i : BasePolicy {
/*
 * Implementations
 */
};
```
which employ the *base-chaining* mechanism. Each of these policies defines some *public methods*. In order for the user to use them, he has to derive from them, by chaining them. For example, to use `Policy0`, `Policy1` and `Policy3`, he has to derive from

```c++
struct Class0 : Policy0<Class0, Policy1<Class0, Policy3<Derived, EmptyBase>>> {};
```

which is limiting in a few ways:

* user has to manually nest the `Policies`, but more importantly
* we cannot define a *general* template class for the user to use, where he would simply specify the `Policies` he wants. Currently he must manually write the class given the policies he wants, as above with `Class0`.

We need a `MakeBase` metaprogram, that will allow us to implement a *general* class template

```c++
template <template <class, class> class ...Policies>
struct Class : MakeBase<Class<Policies...>, Policies...> {};
```

where

```c++
using Class0_ = Class<Policy0, Policy1, Policy3>;
```

`Class0_` is equivalent to `Class0` above.

Using the mechanics described so far, this can be achieved by:
* Transform each template policy into a metafunction using [`ml::F`](../reference/Functional/F.md), and
* Partially evaluate each of them on `Derived` using [`ml::Partial`](../reference/Functional/Partial.md), and
* compose these partial evaluations using [`ml::Compose`](../reference/Functional/Compose.md), and
* evaluate the composition on the `Bottom` base class.

```c++
template <typename Derived, template <class, class> class ...Policies>
using MakeBase = ml::f<ml::Compose<ml::Partial<ml::F<Policies>, Derived>...>, ml::None>;
```


### Currying

With a firm grasp on [partial evaluations](#partial-evaluation), we step a level higher, and take a look at currying. Please take note that *currying* operators in [CppML](https://github.com/ZigaSajovic/CppML) operate on variadic parameter packs (i.e. they can curry more than one argument at a time).

#### Curry

Let `F` be a metafunction `Args... -> Us...`. Than [`ml::Curry<F>`](../reference/Functional/Curry.md) is a metafunction that takes a parameter pack `T0s...`, and returns a metafunction `F': T1s... -> Us...`, in such a way, that `F(T0s..., T1s...) == F'(T1s...)`.

```c++
f:: T0s... -> T1s... -> Us...
```

# Appendix

## Pack expansions and non-pack parameter of alias template

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
