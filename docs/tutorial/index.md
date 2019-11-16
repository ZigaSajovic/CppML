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
    * [`CurryR`](#curryr)
    * [`Use case: A generator of tagged class hierarchies`](#use-case-a-generator-of-tagged-class-hierarchies)
  * [`Functional branching`](#functional-branching)
    * [`Use case: A generator of tagged class hierarchies with conditional branches`](#use-case-a-generator-of-tagged-class-hierarchies-with-conditional-branches) 
  * [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions)
    * [`Use case: Subsetting a std::tuple to its non-class types`](#use-case-subsetting-a-stdtuple-to-its-non-class-types)
  * [`Aliases as type-lambdas`](#aliases-as-type-lambdas)
    * [`Use case: Introspective metafunctions`](#use-case-introspective-metafunctions)
  * [`Reference: Functional`](#reference-functional)
* [`Manipulating parameter packs`](#manipulating-parameter-packs)
  * [`Choosing and Sub-packing`](#choosing-and-sub-packing)
  * [`Appending, Prepending and Inserting`](#appending-prepending-and-inserting)
    * [`Appending multiple elements using partial evaluations`](#appending-multiple-elements-using-partial-evaluations)
  * [`Reference: Pack`](#reference-pack)
* [`Algorithms on parameter packs`](#algorithms-on-parameter-packs)
  * [`Reference: Algorithm`](#reference-algorithm)
* [`Examples`](#further-examples)
  * [`Optimizing the memory layout of std::tuple`](#optimizing-the-memory-layout-of-stdtuple)


## Introduction

---

`CppML` is a metalanguage for `C++`. It was designed to **simplify** the process of **creating** intricate **classes**, by letting the programmer **design** them through **expressions** that feel like **algorithms** in a **functional language**. It strives to be **easy** to **write** and **easy** to **read**, while being **efficient**. It does so by providing [`compositional pipelines`](#pipe) through which [`parameter packs`](#parameter-pack) can flow **without instantiating** new **types**. Our goal is to **give** library developers **programmatic control** over the creation of **class hierarchies** with **metaprograms** that shape their **structure and behaviour** through **metafunctional logic**. This way constructions of **complex designs** are easily encoded in **elegant** and **concise** functional **expressions**.

---

In this tutorial, we will go over the design of the `CppML` language and explore its prominent features in depth. You will learn about [`compositional pipelines`](#pipe) and the flow of [`parameter packs`](#parameter-pack) through them. You will learn about the structure of [`metafunctions`](#metafunction), how to understand their [`metafunction type`](#metafunction-type), and how they [`integrate with pipelines`](#using-pipes).
You will learn how to [`manipulate metafunctions`](#manipulating-metafunctions) using concepts like [`Currying`](#currying), [`Product Maps`](#product-map) and [`Branch Pipes`](#functional-branching), and how to compose them into algorithms that will build your class designs.

Interspersed throughout the tutorial are *use-cases*, where we will formulate a problem and break down its solution into steps, and than translate them into `CppML`. Through them you will learn how to encode construction of (increasingly) complex designs into  **elegant** and **concise** functional **expressions**.

#### Links to `CppML Reference`

Throughout this tutorial, all links with the `ml::` prefix (e.g. [`ml::Map`](../reference/Functional/Map.md)) lead to the [`CppML reference`](../reference/index.md) for that specific metafunction. Each of them provides a specification of its *structure*, a definition of its *metafunction type*, and an *example* of use. You are encouraged to follow them, as you will quickly be able to learn from the [`CppML reference`](../reference/index.md) itself.

## Key Concepts

### Parameter pack

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

One of the pillars of [CppML](https://github.com/ZigaSajovic/CppML) is composability. As such, the ability to chain transformations on [`parameter packs`](#parameter-pack) is a core feature of the language. Concretely, every [`metafunction`](#metafunction) template has, as their last template parameter, a `Pipe` into which it passes the transformed parameter pack. Please see the [`metafunction`](#metafunction) section to see how `pipelines` integrate with `metafunctions` and the [`Using Pipes`](#using-pipes) section for a detailed demonstration of building pipelines.

The reader might be familiar with the concept of pipes from bash ([`operator |`](https://stackoverflow.com/questions/9834086/what-is-a-simple-explanation-for-how-pipes-work-in-bash)), or from R ([`operator %>%`](https://www.rdocumentation.org/packages/pipeR/versions/0.6.1.3/topics/Pipe)), or from Haskel ([`operator >->`](http://hackage.haskell.org/package/pipes)).

### Metafunction

In [CppML](https://github.com/ZigaSajovic/CppML), a `metafunction` is an instantiation of a *template struct* with a *template alias* `f`. All `metafunctions` define, as their last template parameter, a metafunction [`Pipe`](#pipe) into which `f` will pass the transformed [`parameter pack`](#parameter-pack). In *pseudo-c++* this roughly translates into

```c++
template <typename PossibleArgs...,                                // zero of more arguments
          typename Pipe = (default: ml::Identity or ml::ToList)>   // see `Default pipes` below
struct MetaFunction {
  template <typename... Args>
  using f = Pipe::f<                                               // result passed to Pipe
                    ...mfImplementation::f<
                                           PossibleArgs...,
                                           ...Args...>...>;
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

To illustrate the flow of parameter packs through the `pipelines`, lets take the concrete example of `int, char, vector<int>, int, string, double, float`, and send it through `F`.

```c++
int, char, vector<int>, int, string, double, float 
->                                                  // Pivot<2>
vector<int>, int, string, double, float, int, char 
>->                                                 // Pipe to
vector<int>, int, string, double, float, int, char
->                                                  // Head<4>
vector<int>, int, string, double 
>->                                                 // Pipe to
vector<int>, int, string, double 
->                                                  // RemoveIf<IsClass<>>
int, double                                        
>->                                                 // Default Pipe to
int, double
->                                                  // ToList
ml::ListT<int, double>
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

which can than be evaluated

```c++
using T = ml::f<TupleF, int, char>;
static_assert(
          ml::is_same_v<
                  T,
                  std::tuple<int, char>>);
```

We can now alter the previous example, and use `TupleF`, as the [`Pipe`](#pipe) of [`ml::Filter`](../reference/Algorithm/Filter.md)

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
* evaluate the composition on the `ml::None`, making it the bottom base class.

This sequence is easily translated into `CppML`.

```c++
template <typename Derived, template <class, class> class ...Policies>
using MakeBase = ml::f<ml::Compose<ml::Partial<ml::F<Policies>, Derived>...>, ml::None>;
```
which concludes our implementation of `Class` (above), in an elegant *one-liner*. This is the strength of the functional approach to meta design.

### Currying

With a firm grasp on [partial evaluations](#partial-evaluation), we step a level higher, and take a look at currying. Please take note that *currying* operators in [CppML](https://github.com/ZigaSajovic/CppML) operate on variadic parameter packs (i.e. they can curry more than one argument at a time).

#### Curry

Let `F` be a metafunction `Args... -> Us...`. Than [`ml::Curry<F>`](../reference/Functional/Curry.md) is a metafunction that takes a parameter pack `T0s...`, and returns a metafunction `F': T1s... -> Us...`, in such a way, that `F(T0s..., T1s...) == F'(T1s...)`.

```c++
f:: T0s... -> T1s... -> Us...
```

This means that you can imagine the [`ml::Curry<F>`](../reference/Functional/Curry.md) as [partially evaluated metafunction](#partial-evaluation) made by [`lifting the template`](#lifting-templates-to-metafunctions)) of [`ml::Partial`](../reference/Functional/Partial.md) to a metafunction using [`ml::F`](../reference/Functional/F.md), and partially evaluating it on `F` (the template argument of `Curry`). So lets write it:

```c++
template <typename F>
using Curry = ml::Partial<ml::F<ml::Partial>, F>;
```

Note that in `CppML`, [`ml::Curry<F>`](../reference/Functional/Curry.md) is implemented by inheritance instead of an alias, to make it a distinct type. But the logic is the same.

#### CurryR

Please consult the [`CppML reference`](../reference/index.md) for [`ml::CurryR`](../reference/Functional/CurryR.md), which is like [`ml::Curry`](../reference/Functional/Curry.md), except that it partially evaluates from the right (see [`ml::PartialR`](../reference/Functional/PartialR.md)).

#### Use case: A generator of tagged class hierarchies

Suppose have an object holder, which (as in our previous use case) uses *base-chaining*

```c++
template <typename TaggedObject, typename Base>
struct Holder : Base;
```

but each object being held, needs to be *tagged* using an [`ml::Int`](../reference/Vocabulary/Value.md), to both give it a distinct identity, and a static index. As such, assuming

```c++
template <typename Tag, typename Object> struct Param {};
```

each `TaggedObject` is constrained to be `Param<ml::Int<N>, Object>`.

```c++
template <int N, typename Object, typename Base>
struct Holder<Param<ml::Int<N>, Object>, Base> : Base {
  Object object;
  /* Implementation of logic */
};
```

For example, this is used in some implementations of `std::tuple`. One creates a nested hierarchy of such `Holder`s and derives from it. In order to be able to make use of such techniques, we need a metaprogram `MakeBase`

```c++
template <typename ...Ts>
struct Class : MakeBase<Ts...> {
  /* Implementation */
};
```

where `MakeBase<T0, T1, T2, T3>` is equivalent to

```c++
Holder<Param<ml::Int<0>, T0>,
                Holder<Param<ml::Int<1>, T1>,
                                Holder<Param<ml::Int<2>, T2>>,
                                                  Holder<Param<ml::Int<3>, T3>>>>;
```

Using the mechanics described so far, this can be achieved by:

* Zip with `Param` (using [`ml::ZipWith`](../reference/Algorithm/ZipWith.md))
  * the list of type-integers in the range `[0, sizeof...(Ts))`, (which is created using [`ml::Range`](../reference/Pack/Range.md))
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<`[`ml::Int`](../reference/Vocabulary/Value.md)`<0>, ..., `[`ml::Int`](../reference/Vocabulary/Value.md)`<sizeof...(Ts) - 1>>` , and
  * the list made from `Ts...`
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<Ts...>`
* [`ml::Map`](../reference/Functional/Map.md) the resulting parameter pack `Param<ml::Int<Is>, Ts>...`, by the metafunction we get by
  * Currying the metafunction (using [`ml::Curry`](../reference/Functional/Curry.md))
    * made from `Holder` (using [`ml::F`](../reference/Functional/F.md); see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))
* and compose the resulting parameter pack of partially evaluated metafunctions, by having map pass it into `Pipe`
  * which is a metafunction we made from [`ml::Compose`](../reference/Functional/Compose.md) (see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))

This leaves us with a metafunction that is to be evaluated on its most bottom `Base` class. The sequence is easily translated into `CppML`.

```c++
template <typename ...Ts>
using MakeBase_f = ml::f<
    ml::ZipWith<Param, ml::Map<ml::Curry<ml::F<Holder>>, ml::F<ml::Compose>>>,
    ml::Range<>::f<0, sizeof...(Ts)>, ml::ListT<Ts...>>;
```

Which, after using [`ml::None`](../reference/Vocabulary/None.md) as our bottom base class,

```c++
template <typename ...Ts>
using MakeBase = ml::f<MakeBase_f<Ts...>, ml::None>;
```

concludes our implementation of `Class` (above), which remains simple and easy to read.

### Functional branching

There are two main actors behind functional branching in `CppML`. The first is the [`ml::IfElse`](../reference/Functional/IfElse.md) construct, where [`ml::IfElse`](../reference/Functional/IfElse.md)`<`[`ml::Bool`](../reference/Vocabulary/Value.md)`<t_val>>` is a [`metafunction`](#metafunction)

```c++
f:: T, U -> V >-> Pipe
```

that passes to pipe `T` if `t_val` is `true`, and `U` if `t_val` is `false`. In its bare form, it behaves like so:

```c++
using T = ml::f<ml::IfElse<ml::Bool<true>>, int, char>;
static_assert(
    std::is_same_v<
              T, int>);
```

The second is [`ml::BranchPipe`](../reference/Functional/BranchPipe.md), where [`ml::BranchPipe`](../reference/Functional/BranchPipe.md)`<Predicate, IfPipe, ElsePipe>` is a metafunction which passes the [`parameter pack`](#parameter-pack) `Ts...`, to one of two `Pipes`, given the result of invoking the `Predicate`on `Ts...`.

```c++
f:: Ts... -> Ts... >-> (Predicate(Ts...) ? IfPipe : ElsePipe)
```

`BranchPipe` brings the powerful notion of having the execution of metaprograms depend on introspective predicates about types into the language. In other words, it allows us to write meta algorithms that design class hierarchies, that not only stitch them together, but also change and alter their design, based on the types involved in it.

#### Use case: A generator of tagged class hierarchies with conditional branches

Remembering our previous use case in which we created [`A generator of tagged class hierarchies`](#use-case-a-generator-of-tagged-class-hierarchies), where our objects were held by

```c++
template <int N, typename Object, typename Base>
struct Holder<Param<ml::Int<N>, Object>, Base> : Base {
  Object object;
  /* Implementation of logic */
};
```
we note that we did not take advantage of the *empty-base-class* optimization. Because of this, each `Object` occupies at least `1 byte` in the hierarchy, even if they are empty (this is due to the fact that each object needs a unique address). If we instead wrote our `Holder` as `BaseHolder`,

```c++
template <int N, typename Object, typename Base>
struct BaseHolder<Param<ml::Int<N>, Object>, Base> : Object, Base {
  /* Implementation of logic */
};
```

all empty `Objects` (of different type) could share the address, and hence gain memory efficiency by the *empty base class* optimization. But the problem with this approach is that you can only derive from *class types*. Hence, if we simply substituted `Holder` for `BaseHolder` in our metaprogram from [`A generator of tagged class hierarchies`](#use-case-a-generator-of-tagged-class-hierarchies), it would fail to compile when any type in the invoking parameter pack `Ts...` was a *non-class* type. The solution is to let the metaprogram conditionally choose which class will hold the `Object`, depending on whether it is a class or not.

Hence, we want to alter the metaprogram `MakeBase` from [`A generator of tagged class hierarchies`](#use-case-a-generator-of-tagged-class-hierarchies), such that `MakeBase<int, string, char, vector<int>>` is equivalent to

```c++
Holder<Param<ml::Int<0>, int>,
               BaseHolder<Param<ml::Int<1>, string>,
                           Holder<Param<ml::Int<2>, char>>,
                                          BaseHolder<Param<ml::Int<3>, vector<int>>>>>;
```

We will accomplish this by using `BranchPipe`, which will choose between two metafunctions as pipes, namely the [`ml::Curry`](../reference/Functional/Curry.md)`<`[`ml::F`](../reference/Functional/F.md)`<Holder>>` and [`ml::Curry`](../reference/Functional/Curry.md)`<`[`ml::F`](../reference/Functional/F.md)`<BaseHolder>>`, given the result of the [`ml::IsClass`](../reference/TypeTraits/IsClass.md) predicate. This will be used in the place where we used [`ml::Curry`](../reference/Functional/Curry.md)`<`[`ml::F`](../reference/Functional/F.md)`<Holder>>` in the [`A generator of tagged class hierarchies`](#use-case-a-generator-of-tagged-class-hierarchies). With this addition, the procedure reads:

* Zip with `Param` (using [`ml::ZipWith`](../reference/Algorithm/ZipWith.md))
  * the list of type-integers in the range `[0, sizeof...(Ts))`, (which is created using [`ml::Range`](../reference/Pack/Range.md))
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<`[`ml::Int`](../reference/Vocabulary/Value.md)`<0>, ..., `[`ml::Int`](../reference/Vocabulary/Value.md)`<sizeof...(Ts) - 1>>`, and
  * the list made from `Ts...`
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<Ts...>`
* [`ml::Map`](../reference/Functional/Map.md) the resulting parameter pack `Param<ml::Int<Is>, Ts>...`, by the metafunction we get by:
  * Branching on the `Predicate` (using [`ml::BranchPipe`](../reference/Functional/BranchPipe.md)) we get by:
    * Extract the `T` from `Param<Int<I>, T>`
      * [`ml::Unwrap`](../reference/Functional/Unwrap.md) the parameter pack from `Param<Int<I>, T>` (see [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions)) into
      * [`ml::Get`](../reference/Pack/Get.md)`<0>`, and `Pipe` it to [`ml::IsClass`](../reference/TypeTraits/IsClass.md)
  * If `T` *is a class type*:
    * Currying the metafunction (using [`ml::Curry`](../reference/Functional/Curry.md))
      * made from `BaseHolder` (using [`ml::F`](../reference/Functional/F.md); see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))
  * else (if the `T` is a *non-class type*):
    * Currying the metafunction (using [`ml::Curry`](../reference/Functional/Curry.md))
      * made from `Holder` (using [`ml::F`](../reference/Functional/F.md); see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))
* and compose the resulting parameter pack of partially evaluated metafunctions, by having map pass it into `Pipe`
  * which is a metafunction we made from [`ml::Compose`](../reference/Functional/Compose.md) (see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))

This leaves us with a metafunction that is to be evaluated on its most bottom `Base` class. The sequence is easily translated into `CppML`.

```c++
template <typename... Ts>
using MakeBase_f = ml::f<
    ml::ZipWith<Param,
                ml::Map<ml::BranchPipe<ml::Unwrap<ml::Get<0, ml::IsClass<>>>,
                                       ml::Curry<ml::F<BaseHolder>>,
                                       ml::Curry<ml::F<Holder>>>,
                        ml::F<ml::Compose>>>,
    ml::Range<>::f<0, sizeof...(Ts)>, ml::ListT<Ts...>>;
```

Which, after using [`ml::None`](../reference/Vocabulary/None.md) as our bottom base class,

```c++
template <typename ...Ts>
using MakeBase = ml::f<MakeBase_f<Ts...>, ml::None>;
```

concludes our implementation. Looking at the metaprogram `MakeBase`, it is a direct translation of our procedure in the bullet list, into the compositional pipelines of `CppML`. We hope it sheds light on the purpose of `CppML`: to give you control over class design through expressions that feel like algorithms in a functional language.

### Unwrapping template arguments into metafunctions

Templates are constructs which wrap [`parameter packs`](#parameter-pack). For example

```c++
using Tpl = std::tuple<int, char, string, bool>;
```

`Tpl` is the [`parameter pack`](#parameter-pack) `int, char, string, bool` that is wrapped in a `std::tuple`. A different example you might encounter using `CppML`, is [`ml::ListT`](../reference/Vocabulary/List.md), when you store a result of a metacomputation, where the final `Pipe` was [`ml::ToList`](../reference/Functional/ToList.md).

Suppose you now want to invoke a metafunction on the [`parameter pack`](#parameter-pack) being wrapped. `CppML` defines [`ml::Unwrap`](../reference/Functional/Unwrap.md) with the metafunction type

```c++
f:: Template<Ts...> -> Ts... >-> Pipe
```

which is exactly what we need. For example, this can be used to compute the number of template parameters, by unwrapping them into [`ml::Length`](../reference/Pack/Length.md)

```c++
f:: Template<Ts...> -> Ts... >-> ml::Length
```

#### Use case: Subsetting a `std::tuple` to its non-class types

Suppose we wish to create a sub-tuple of `Tpl`, which will contain only the elements which are non-class types. Using what we have seen so far, this is accomplished by:

* Unwrap the parameter pack (using [`ml::Unwrap`](../reference/Functional/Unwrap.md)) into
* Removing all elements of that are a class type, and
  * [`ml::RemoveIf`](../reference/Algorithm/RemoveIf.md)`<`[`ml::IsClass`](../reference/TypeTraits/IsClass.md)`<>>`
* Pipe into `std::tuple` which was [`lifted into a metafunction`](#lifting-templates-to-metafunctions)
  * [`ml::F`](../reference/Functional/F.md)`<std::tuple>`

This sequence is easily translated into `CppML`,

```c++
using NonClassSubtuple = ml::Unwrap<ml::RemoveIf<ml::IsClass<>, ml::F<std::tuple>>>;
```

and the `NonClassSubtuple` [`metafunction`](#metafunction) is ready to use:

```c++
using NonClassSubtuple = ml::Unwrap<ml::RemoveIf<ml::IsClass<>, ml::F<std::tuple>>>;
using SubTpl = ml::f<NonClassSubtuple, Tpl>;
static_assert(
        std::is_same_v<
              T,
              std::tuple<
                int, char, bool>>);

```

### Aliases as type-lambdas

As we have already touched on, it is possible to [`lift an alias template into a metafunction`](#lifting-templates-to-metafunctions). This also means that you are able to write [`metafunctions`](#metafunction) on the spot by lifting aliases.

One application of this concept is to use it for a different way of [`partially evaluating`](#partial-evaluation) a metafunction. For example, writing an `IsInt` metafunction can be written using [`ml::IsSame`](../reference/TypeTraits/IsSame.md), like so 

```c++
template <typename T>
using IsInt_f = ml::f<ml::IsSame<>, T, int>;
using IsInt = ml::F<IsInt_f>;
```

Note that [`ml::F`](../reference/Functional/F.md) also accepts a [`Pipe`](#pipe), allowing us to turn the `alias template` `IsInt_f` into a proper [`metafunction`](#metafunction)

```c++
template <typename Pipe = ml::Identity>
using IsInt = ml::F<IsInt_f, Pipe>;
```

which has standard [`pipe`](#pipe)-ing syntax.

```c++
using T = ml::f<
                IsInt<ml::Not<>>,
                double>;

static_assert(
        std::is_same_v<
            ml::Bool<true>,
            T>);
```

#### Use case: Introspective metafunctions

Introspection can be implemented by checking whether an invocation of a [`metafunction`](#metafunction) on some parameter pack `Ts...` is *ill-formed* or not. These checks can be performed by [`ml::IsValid`](../reference/TypeTraits/IsValid.md), which maps a metafunction `F` and arguments `Ts...`, to an [`ml::Bool`](../reference/Vocabulary/Value.md). We can create metafunctions, whose validity answers our introspective questions.

Suppose we are interested in whether a type defines a `.size()` method. Than, we create a `type lambda` which attempts to use it, like so:

```c++
template <typename _T>
using HasSize_f = decltype(std::declval<_T>().size());
```

which can be used with [`ml::IsValid`](../reference/TypeTraits/IsValid.md) by [`lifting it to a metafunctions`](#lifting-templates-to-metafunctions).

```c++
using T = ml::f<
                ml::IsValid<>,
                ml::F<HasSize_f>,
                std::vector<int>>;

static_assert( std::is_same_v<
                          T, ml::Bool<true>>);
```

We can now define a proper metafunction `HasSize`, by partially evaluating [`ml::IsValid`](../reference/TypeTraits/IsValid.md) on [`ml::F`](../reference/Functional/F)`<HasSize_f>`. We will also give it a `Pipe`, to make it a proper [`metafunction`](#metafunction).

```c++
template <typename Pipe = ml::Identity>
using HasSize = ml::Partial<ml::IsValid<Pipe>, ml::F<HasSize_f>>;
```

We now have a `HasSize` metafunction, which can be used in compositional pipelines of `CppML` as any other [`metafunction`](#metafunction). Lets use it to [`ml::Filter`](../reference/Algorithm/Filter.md) a parameter pack for types which have a `.size()` method.

```c++
using T = ml::f<
                ml::Filter<HasSize<>>,
                std::vector<int>, int, std::map<int, int>>;
static_assert(
        std::is_same_v<
                T,
                ml::ListT<
                    std::vector<int>, std::map<int, int>>>);
```

The other thing one might want to do is get the result of the invocation of a [`metafunction`](#metafunction) on `Ts...` if it is not *ill-formed*, and get a `Default` type, if it is *ill-formed*. The construct that enables this is the [`ml::IfValidOr`](../reference/TypeTraits/IfValidOr.md).

To demonstrate, suppose we need a metafunction that extracts the `ValueType` alias of a type if it defines one, or return [`ml::None`](../reference/Vocabulary/None.md), if it does not.

```c++
struct A { using ValueType = int;};
struct B {};

template <typename _T>
using GetType_f = typename _T::ValueType;
```

We will define a [`metafunction`](#metafunction) by partially evaluating [`ml::IfValidOr`](../reference/TypeTraits/IfValidOr.md) on [`ml::None`](../reference/Vocabulary/None.md) (as `Default`) and [`ml::F`](../reference/Functional/F)`<GetType_f>`. We will also give it a `Pipe`, to make it a proper [`metafunction`](#metafunction).

```c++
template <typename Pipe = ml::Identity>
using GetValueType = ml::Partial<ml::IfValidOr<Pipe>, ml::None, ml::F<GetType_f>>;
```

We now have a `GetValueType` metafunction, which can be used in compositional pipelines of `CppML` as any other [`metafunction`](#metafunction):

```c++
using T = ml::f<
            ml::Map<GetValueType>,
            A, B>;


static_assert(
        std::is_same_v<
                T,
                ml::ListT<
                  int, ml::None>>);
```

This demonstrates how you can include introspective logic in your class design using `type lambdas`.

### Reference: `Functional`

The constructs presented in this section live in the [`Functional`](../reference/index.md#Functional) header. The header also contains other constructs, which were not addressed in the section. Given what you have learned so far, you are able to find the remaining constructs in the table below, and learn about each from its `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                               | Description                                          | Type of `f` in `::f >-> Pipe`  |
|---------------------------------------------------------|------------------------------------------------------|--------------------------------|
| [`Bind`](../reference/Functional/Bind.md)               | Metafunction with args bound to specific positions.  | `Ts... -> Us...`               |
| [`BranchPipe`](../reference/Functional/BranchPipe.md)   | Branches to one of two `Pipes`, given a `Predicate`. | `Ts... -> Ts...`               |
| [`Compose`](../reference/Functional/Compose.md)         | Composition of metafunctions `Fs...`.                | `Ts... -> F0(F1(...(Fn(Us...)` |
| [`Constant`](../reference/Functional/Constant.md)       | Metafunction that always returns `U`.                | `Ts... -> U`                   |
| [`Curry`](../reference/Functional/Curry.md)             | The Curry (from the left) operator                   | `T0s... -> T1s... -> Us...`    |
| [`CurryR`](../reference/Functional/CurryR.md)           | The Curry (from the right) operator                  | `T1s... -> T0s... -> Us...`    |
| [`DelayedEval`](../reference/Functional/DelayedEval.md) | Delays an evaluation until compiler knows the arity. | `Ts... -> Us...`               |
| [`f`](../reference/Functional/Invoke.md)                | Invokes the `f` alias of the metafunction `F`        | `Ts... -> F::f<Ts...>`         |
| [`F`](../reference/Functional/F.md)                     | Lifts a template to a metafunction                   | `Ts... -> Template<Ts...>`     |
| [`Identity`](../reference/Functional/Identity.md)       | Identity metafunction.                               | `T -> T`                       |
| [`IfElse`](../reference/Functional/IfElse.md)           | Chooses between `T` and `U`.                         | `T, U -> V`                    |
| [`InvokeWith`](../reference/Functional/InvokeWith.md)   | Invokes the metafunction on `Ts...`                  | `Ts... -> Us... -> Us...`      |
| [`Map`](../reference/Functional/Map.md)                 | Maps `Ts...` by `F`.                                 | `Ts... -> F(Ts)...`            |
| [`Partial`](../reference/Functional/Partial.md)         | Partial evaluation of `F` on `T0s...` from the left  | `T1... -> F(T0..., T1...)`     |
| [`PartialR`](../reference/Functional/PartialR.md)       | Partial Evaluation of `F` on `T1s...` from the right | `T0... -> F(T0..., T1...)`     |
| [`Product`](../reference/Functional/Product.md)         | Product of metafunctions `Fs...`                     | `Ts... -> Fs(Ts...)...`        |
| [`ProductMap`](../reference/Functional/ProductMap.md)   | Product map of metafunctions `Fs`                    | `Ts... -> Fs(Ts)...`           |
| [`ToList`](../reference/Functional/ToList.md)           | Wraps `Ts...` in an `ListT`                          | `Ts... -> ListT<Ts...>`        |
| [`ToValue`](../reference/Functional/ToValue.md)         | Invokes `::value` on `Ts...`                         | `Value<Ts, ts>... -> ts...`    |
| [`Unwrap`](../reference/Functional/Unwrap.md)           | Unwraps the template around `Ts...`                  | `Template<Ts...> -> Ts...`     |

## Manipulating parameter packs

[`Parameter packs`](#parameter-pack) are the streams of types that flow through our [`pipelines`](#pipe). As such, it is necessary to have a good grasp of the mechanics that control them, as you are sending them through pipes.

### Choosing and Sub-packing

We can extract the first element of a [`parameter pack`](#parameter-pack) using [`ml::First`](../reference/Pack/Front.md)

```c++
using T = ml::f<ml::Front<>, int, char, bool>;
static_assert(
        std::is_same_v<
              T, int>);
```

or extract an element at arbitrary position using [`ml::Get`](../reference/Pack/Get.md).

```c++
using T = ml::f<ml::Get<1>, int char bool>;
static_assert(
        std::is_same_v<
              T, char>);
```

We can sub-pack the [`parameter pack`](#parameter-pack) to the first `N` elements using [`ml::Head`](../reference/Pack/Head.md)

```c++
using T = ml::f<ml::Head<2>, int, char, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                int, char>>);
```

or sub-pack it to the last `N` elements using [`ml::Tail`](../reference/Pack/Tail.md)

```c++
using T = ml::f<ml::Tail<2>, int, char, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                char, bool>>);
```

Note that all constructs that manipulate [`parameter packs`](#parameter-pack) are just metafunctions, and can be used with `Pipes`.

```c++
using T = ml::f<ml::Tail<2, ml::Map<ml::IsClass<>>>, int, string, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                ml::Bool<true>, ml::Bool<false>>>);
```

### Appending, Prepending and Inserting

You can append an element to a [`parameter pack`](#parameter-pack) by [`ml::Append`](../reference/Pack/Append.md)

```c++
using T = ml::f<ml::Append<string, ml::Map<ml::IsClass<>>>, int, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                ml::Bool<false>, ml::Bool<false>, ml::Bool<true>>>);
```

or prepend it using [`ml::Prepend`](../reference/Pack/Prepend.md).

```c++
using T = ml::f<ml::Prepend<string, ml::Map<ml::IsClass<>>>, int, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                ml::Bool<true>, ml::Bool<false>, ml::Bool<false>>>);
```

To insert an element at `N`-th position, use [`ml::Insert`](../reference/Pack/Insert.md)

```c++
using T = ml::f<ml::Insert<, 1, string, ml::Map<ml::IsClass<>>>, int, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                ml::Bool<false>, ml::Bool<true>, ml::Bool<false>>>);
```

**NOTE**

As an exercise, think about how you could implement [`ml::Insert`](../reference/Pack/Insert.md), using [`ml::Pivot`](../reference/Algorithm/Pivot.md) (see [`Algorithms on parameter packs`](#algorithms-on-parameter-packs)) and [`ml::Prepend`](../reference/Pack/Prepend.md).

* Pivot `N`-th element to the front
* Prepend the element
* Pivot original (now at position `sizeof...(Ts) - N + 1`) to the front

Because this is how [`ml::Insert`](../reference/Pack/Insert.md) is implemented, you can look at its [implementation](../../include/CppML/Pack/Insert.hpp).

#### Appending multiple elements using partial evaluations

Because, as explained in [`parameter packs`](#parameter-packs), you cannot hold a [`parameter pack`](#parameter-pack), but only pass it forward (to a `Pipe`), appending to a [`parameter pack`](#parameter-pack) always happens as parameter passing. Hence, appending `Us...` to `Ts...` as we pass to `F`, is equivalent to an invocation of a partially evaluated `F`.

```c++
using T = ml::f<ml::Partial<ml::Map<ml::IsClass<>>>, string>, int, bool>;
static_assert(
        std::is_same_v<
              T,
              ml::ListT<
                ml::Bool<true>, ml::Bool<false>, ml::Bool<false>>>);
```

**NOTE**

The same holds for prepending, but we partially evaluate from the right using [`ml::PartialR`](../reference/Functional/PartialR.md). A similar procedure can also be performed for inserting, if we include some [`ml::Pivot`](../reference/Algorithm/Pivot.md)-ing.

### Reference: `Pack` 

There are other constructs for working with parameter packs, which we did not mention in this section. Those include [`ml::Range`](../reference/Pack/Range.md), which generates a [`parameter pack`](#parameter-pack) of type-values [`ml::Int`](../reference/Vocabulary/Value.md), in the range `[From, To)`, with a `Step` that default to `1`.

```c++
using Sequence = ml::Range<ml::ToList>::f<0, 6, 2>;
static_assert(
        std::is_same<
            Sequence,
            ml::List<
                ml::Int<0>, ml::Int<2>, ml::Int<4>>>);
```

and [`ml::Length`](../reference/Pack/Length.md) which gives you the number of elements of a parameter pack. To compute the number of template arguments of type, combine it with [`ml::Unwrap`](../reference/Functional/Unwrap.md), like we did in [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions).

Constructs for manipulating [`parameter packs`](#parameter-pack) have an associated header `CppML/Pack.hpp` and a directory of the same name `CppML/Pack`. Every construct has a dedicated `.hpp` header inside the `CppML/Pack/` directory. For example, the construct, [`ml::Head`](../reference/Algorithm/Head.md), can be found in the `CppML/Algorithm/Head.hpp`. Hence, you can include all algorithms at once using `#include <CppML/Pack.hpp>`, or include only the ones you want (e.g. `#include <CppML/Pack/Head.hpp>`

Find the construct of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                             | Description                              | Type of `f` in `::f >-> Pipe`                     |
|-------------------------------------------------------|------------------------------------------|---------------------------------------------------|
| [`Drop`](../reference/Pack/Drop.md)                   | Drops first `N` of `Ts...`               | `T1, ... Tn, Ts... -> Ts...`                      |
| [`Front`](../reference/Pack/Front.md)                 | Gets first element of `Ts...`            | `T, Ts... -> T`                                   |
| [`Get`](../reference/Pack/Get.md)                     | Gets `N`-th element of `Ts...`           | `T1, ... Tn, Ts... -> Tn`                         |
| [`Head`](../reference/Pack/Head.md)                   | First `N` of `Ts...`                     | `T1, ... Tn, Ts... -> T1, ... Tn`                 |
| [`Insert`](../reference/Pack/Insert.md)               | Inserts `U` as `N`-th element of `Ts...` | `T1, ... Tn, Ts... -> T1, ... U, Tn, Ts... `      |
| [`Length`](../reference/Pack/Length.md)               | Length of `Ts...`                        | `Ts... -> Int<sizeof...(Ts)`                      |
| [`Concat`](../reference/Pack/Concat.md)               | Concatenates `N` templates `T`           | `T<A0s...>... -> T<A0s..., A1s..., Ans...>`       |
| [`PackExtractor`](../reference/Pack/PackExtractor.md) | Extracts `N`-th element.                 | `Int<N> -> T`                                     |
| [`Prepend`](../reference/Pack/Prepend.md)             | Prepends `T` to `Ts...`                  | `Ts... -> T, Ts...`                               |
| [`Range`](../reference/Pack/Range.md)                 | Pack of `Int<I>` in range                | `From, To -> Int<From>..., Int<To - 1>`           |
| [`Tail`](../reference/Pack/Tail.md)                   | Last `N` of `Ts...`                      | `Ts..., T_{-N}, ... T_{-1} -> T_{-N}, ... T_{-1}` |

**NOTE**

Constructs such as [`ml::Pivot`](../reference/Algorithm/Pivot.md) and [`ml::Rotate`](../reference/Algorithm/Rotate.md) are part of the [`Algorithm`](../reference/index.md#algorithm) header.

## Algorithms on parameter packs

We have already meet a few of the algorithms (like [`ml::ZipWith`](../reference/Algorithm/ZipWith.md), [`ml::Filter`](../reference/Algorithm/Filter.md), etc.) on our way to this point of the tutorial. As was apparent from their usage, they are no different from any other [`metafunction`](#metafunction) operating on [`parameter packs`](#parameter-pack), so there is not much extra to be said about them. But what is important, is to know how to find them, when you need them.

Algorithms have an associated header `CppML/Algorithm.hpp` and a directory of the same name `CppML/Algorithm`. Every algorithm has a dedicated `.hpp` header inside the `CppML/Algorithm/` directory. For example, the algorithm, [`ml::Sort`](../reference/Algorithm/Sort.md), can be found in the `CppML/Algorithm/Sort.hpp`. Hence, you can include all algorithms at once using `#include <CppML/Algorithm.hpp>`, or include only the ones you want (e.g. `#include <CppML/Algorithm/Sort.hpp>`

### Reference: `Algorithm`

We provide a detailed [`CppML reference`](../reference/index.md), which also contains an [`Algorithm`](../reference/index.md#algorithm) section. Please find the algorithm of your interest in the table below. Each of them has it own `reference page`, where you can find a *specification of its structure*, a definition of its *metafunction type*, and an *example of use*.

| Construct                                                      | Description                                                    | Type of `f` in `::f >-> Pipe`   |
|----------------------------------------------------------------|----------------------------------------------------------------|---------------------------------|
| [`AllOf`](../reference/Algorithm/AllOf.md)                     | Checks if a `Predicate` holds for all of `Ts...`.              | `Ts... -> Bool<t>`              |
| [`AnyOf`](../reference/Algorithm/AnyOf.md)                     | Checks if a `Predicate` holds for any of `Ts...`.              | `Ts... -> Bool<t>`              |
| [`Contains`](../reference/Algorithm/Contains.md)               | Checks is `Ts...` contains `T`.                                | `Ts... -> Bool<t>`              |
| [`CountIf`](../reference/Algorithm/CountIf.md)                 | Counts `Ts...` for which the `Predicate` holds.                | `Ts... -> Bool<t>`              |
| [`Filter`](../reference/Algorithm/Filter.md)                   | Filters `Ts...`, for which the `Predicate` holds.              | `Ts... -> Us...`                |
| [`FilterIds`](../reference/Algorithm/FilterIds.md)             | Filters indexes of `Ts...`, for which the `Predicate` holds.   | `Ts... -> Int<Is>...`           |
| [`FindIf`](../reference/Algorithm/FindIf.md)                   | Index of `Ts...` for which the `Predicate` holds.              | `Ts... -> Int<I>`               |
| [`FindIfNot`](../reference/Algorithm/FindIfNot.md)             | Index of `Ts...` for which the `Predicate` does not hold.      | `Ts... -> Int<I>`               |
| [`GroupBy`](../reference/Algorithm/GroupBy.md)                 | Groups `Ts...`, given their image under `By`.                  | `Ts... -> ListT<Us...>...`      |
| [`InclusiveScan`](./Algorithm/InclusiveScan.md)                | Inclusive scan under the binary `F`.                           | `Ts... -> T0, F(T0, T1), ...`   |
| [`MaxElement`](../reference/Algorithm/MaxElement.md)           | Get maximal element, given a `Comparator`.                     | `Ts... -> U`                    |
| [`NoneOf`](../reference/Algorithm/NoneOf.md)                   | Checks if a `Predicate` holds for none of `Ts...`.             | `Ts... -> Bool<t>`              |
| [`Partition`](../reference/Algorithm/Partition.md)             | Partitions `Ts...` given a `Predicate`.                        | `Ts... -> ListT<Us...>...`      |
| [`PartitionIds`](../reference/Algorithm/PartitionIds.md)       | Partitions indexes of `Ts...` given a `Predicate`.             | `Ts... -> ListT<Int<Is>...>...` |
| [`Pivot`](../reference/Algorithm/Pivot.md)                     | Pivots `Ts...` around the `N`-th element, making it the first. | `Ts... -> Us...`                |
| [`Reduce`](../reference/Algorithm/Reduce.md)                   | Reduce `Ts...`, given an accumulator `F`.                      | `Init, Ts... -> U`              |
| [`RemoveIdsIf`](../reference/Algorithm/RemoveIdsIf.md)         | Removes indexes of `Ts...` for which the `Predicate` holds.    | `Ts... -> Us...`                |
| [`RemoveIf`](../reference/Algorithm/RemoveIf.md)               | Removes elements of `Ts...` for which the `Predicate` holds.   | `Ts... -> Int<Is>...`           |
| [`ReplaceIf`](../reference/Algorithm/ReplaceIf.md)             | Replace `Ts...`, for which the `Predicate` holds, by `U`.      | `Ts... -> Us...`                |
| [`Rotate`](../reference/Algorithm/Rotate.md)                   | Pivots `Ts...` in the range `[First, Middle, Last)`.           | `Ts... -> Us...`                |
| [`Sort`](../reference/Algorithm/Sort.md)                       | Sorts `Ts...`, given a `Comparator`.                           | `Ts... -> Us...`                |
| [`UniqueCompare`](../reference/Algorithm/UniqueCompare.md)     | Unique elements of `Ts...`, given a `Comparator`.              | `Ts... -> Us...`                |
| [`Unique`](../reference/Algorithm/Unique.md)                   | Unique elements of `Ts...`.                                    | `Ts... -> Us...`                |
| [`ZipWith`](../reference/Algorithm/ZipWith.md)                 | Zips two lists with a `With` template.                         | `Ts... -> With<Us...>...`       |
| [`ZipWithVariadic`](../reference/Algorithm/ZipWithVariadic.md) | Zips two lists with a variadic `With` template.                | `Ts... -> With<Us...>...`       |


## Examples

### Optimizing the memory layout of `std::tuple`

The following is a condensed version of the post [Optimizing the memory layout of `std::tuple`](https://github.com/ZigaSajovic/optimizing-the-memory-layout-of-std-tuple). The optimization comes from considering the way in which objects are laid out in memory (remember that they must be [naturally aligned](https://en.wikipedia.org/wiki/Data_structure_alignment) and thus padding may be required).
We implement a class `Tuple`, which is an interface wrapper around `std::tuple`. It works by approximating the optimal permutation by the `Permutation` that sorts the types by their `alignment`. It than lays the objects out in memory in that order. It holds the `Permutation` as its template argument, and uses it to internally redirect the users indexing (hence the user can be oblivious to the permutation).

Please see the original post [Optimizing the memory layout of `std::tuple`](https://github.com/ZigaSajovic/optimizing-the-memory-layout-of-std-tuple), where the entire solution is constructed step by step.

Before we begin, take a look at the result.

```c++

  Tuple<char, int, char, int, char, double, char> tup{'a', 1,   'c', 3,
                                                      'd', 5.0, 'e'};
  std::cout << "Size of out Tuple: " << sizeof(tup) << " Bytes" << std::endl;

  std::tuple<char, int, char, int, char, double, char> std_tup{'a', 1,   'c', 3,
                                                               'd', 5.0, 'e'};
  std::cout << "Size of out std::tuple: " << sizeof(std_tup) << " Bytes"
            << std::endl;

  std::cout << "Actual size of data: "
            << 4 * sizeof(char) + 2 * sizeof(int) + sizeof(double) << " Bytes"
            << std::endl;

  std::cout << get<2>(tup) << " == " << std::get<2>(std_tup) << std::endl;
  assert(tup == std_tup);
```
---
> Size of Tuple:  24 Bytes  
Size of std::tuple: 40 Bytes  
Actual size of data: 20 Bytes  
c == c
---
We notice that the *std::tuple* has **20 Bytes** of **wasted** space (making it **twice** as big as the actual data), while *Tuple* only has **4 Bytes** of **wasted** space.

| **class**  | **size [B]** | **efficiency** |  
|:----------:|:------------:|:--------------:|  
| Data       | 20           | 1              |  
| Tuple      | 24           | 0.84           |  
| std::tuple | 40           | 0.5            |  


#### Class Building Metaprogram

We want a `TupleBase` wrapper of a `std::tuple`, which will

```c++
template <typename Permutation, typename StdTuple> struct TupleBase;
template<int ...Is, typename ...Ts>
struct TupleBase<
            ml::ListT<ml::Int<Is>...>,
            std::tuple<Ts...>> {
/* Implementation */
};
```

have the `Permutation` that sorts the types by their `alignment` as its first template parameter, and the already permuted `std::tuple` as its second. Hence, we need a `MakeBase` metafunction, which will allow us to implement `Tuple` class like

```c++
template <typename... Ts> struct Tuple : MakeBase<Ts...> {
  using MakeBase<Ts...>::MakeBase;
};
```

On a concrete example, we want `MakeBase`

```c++
using TB0 = MakeBase<char, int, char, int, char, double, char>;
using TB1 = 
    TupleBase<ml::ListT<ml::Int<5>, ml::Int<3>, ml::Int<1>, ml::Int<6>, ml::Int<4>,
                        ml::Int<2>, ml::Int<0>>,
              std::tuple<double, int, int, char, char, char, char>>;
static_assert(
      std::is_same_v<TB0, TB1>);
```

This is achieved by the following sequence:

* Zip with `Param` (using [`ml::ZipWith`](../reference/Algorithm/ZipWith.md))
  * the list of type-integers in the range `[0, sizeof...(Ts))`, (which is created using [`ml::Range`](../reference/Pack/Range.md))
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<`[`ml::Int`](../reference/Vocabulary/Value.md)`<0>, ..., `[`ml::Int`](../reference/Vocabulary/Value.md)`<sizeof...(Ts) - 1>>`, and
  * the list made from `Ts...`
    * [`ml::ListT`](../reference/Vocabulary/List.md)`<Ts...>`
* [`ml::Sort`](../reference/Algorithm/Sort.md) the resulting parameter pack `Param<ml::Int<Is>, Ts>...`, with the `Comparator` that takes the `alignment`of the `T`.
  * `Comparator: P0, P1 -> Bool<t>`
  * We [`ml::Map`](../reference/Functional/Map.md) (the `P0` and `P1`) by:
    * [`ml::Unwrap`](../reference/Functional/Unwrap.md) the parameter pack from `Param<Int<I>, T>` (see [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions)), and
    * extract the second element (`T`) using [`ml::Get`](../reference/Pack/Get.md), and
    * pipe the extracted `T` into [`ml::AlignOf`](../reference/TypeTraits/AlignOf.md)
  * and pipe the alignments into [`ml::Greater`](../reference/Arithmetic/Greater.md)
* We than split the sorted parameter pack `Param<ml::Int<Is>, Ts>...` into `TupleBase<ml::ListT<ml::Int<Is>...>, std::tuple<Ts...>>` by:
  * create a [`ml::ProductMap`](../reference/Functional/ProductMap.md) of:
    * [`ml::Map`](../reference/Functional/Map.md) of extractors of the `ml::Int<i>`:
      * [`ml::Unwrap`](../reference/Functional/Unwrap.md) the parameter pack from `Param<Int<I>, T>` (see [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions)), and
      * extract the first element (`ml::Int<I>`) using [`ml::Get`](../reference/Pack/Get.md), and
      * pipe into [`ml::ToList`](../reference/Functional/ToList.md)
    * [`ml::Map`](../reference/Functional/Map.md) of extractors of the `T`:
      * [`ml::Unwrap`](../reference/Functional/Unwrap.md) the parameter pack from `Param<Int<I>, T>` (see [`Unwrapping template arguments into metafunctions`](#unwrapping-template-arguments-into-metafunctions)), and
      * extract the second element (`T`) using [`ml::Get`](../reference/Pack/Get.md), and
      * pipe into the metafunction created from `std::tuple` (using [`ml::F`](../reference/Functional/F.md); see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions)),
    * and `Pipe`into the metafunction created from `TupleBase` (using [`ml::F`](../reference/Functional/F.md); see [`Lifting templates to metafunctions`](#lifting-templates-to-metafunctions))

This sequence is easily translated to `CppML`:

```c++
template <typename ...Ts>
using MakeBase = ml::f<
    ml::ZipWith<
        Param,
        ml::Sort<ml::Map<ml::Unwrap<ml::Get<1, ml::AlignOf<>>>, ml::Greater<>>,
                 ml::Product<ml::Map<ml::Unwrap<ml::Get<0>>>,
                             ml::Map<ml::Unwrap<ml::Get<1>>, ml::F<std::tuple>>,
                             ml::F<TupleBase>>>>,
    ml::Range<>::f<0, sizeof...(Ts)>, ml::ListT<Ts...>>;
```

We will also need a metafunction that will compute the inverse permutation for an index `I`, which will allow us to internally redirect users indexing. This is done by locating the index of `I` in the permutation (using [`ml::FindIf`](../reference/Algorithm/FindIf.md). Assuming access to `Permutation` indexes `Is...` (inside the `TupleBase`, this is done by

```c++
template <typename I>
using Index = ml::f<ml::FindIf<ml::Partial<ml::IsSame<>, I>>, Is...>;
```

#### TupleBase interface

The `TupleBase` implementation is minimal. It will have:
* the permuted `std::tuple` member `_tuple`
  * from its second template argument
* `f` alias which will compute the inverse permutation for an index `I`
* a delegate constructor:
  * It will forward the arguments `Us...` as a tuple to the `work construcotr`
* a `work constructor`:
  * it will initialize the `_tuple` member by:
    * permuting the arguments of the forwarding tuple into its initializer
      * `std::get<Is>(fwd)...` 
* the `get<I>()` friend function, which:
  * will use the `f` alias to invert `I` in the `Permutation`
  * and forward the inverted index to `std::get`

In code, this looks like this:

```c++
template <int... Is, typename... Ts>
struct TupleBase<ml::ListT<ml::Int<Is>...>, std::tuple<Ts...>> {
private:
  std::tuple<Ts...> _tuple;
  template <typename... Us>
  TupleBase(ml::_, std::tuple<Us...> &&fwd) // work constructor
      : _tuple{
            static_cast<ml::f<ml::Get<Is>, Us...> &&>(std::get<Is>(fwd))...} {}

public:
  template <typename... Us>
  TupleBase(Us &&... us) // delegate constructor
      : TupleBase{ml::_{}, std::forward_as_tuple(static_cast<Us &&>(us)...)} {}
  template <typename I> // Compute the inverse index
  using f = ml::f<ml::FindIf<ml::Partial<ml::IsSame<>, I>>, ml::Int<Is>...>;
  template <int I, typename... Us>
  friend decltype(auto) get(TupleBase<Us...> &tup);
};

template <int I, typename... Us> decltype(auto) get(TupleBase<Us...> &tup) {
  return std::get<ml::f<TupleBase<Us...>, ml::Int<I>>::value>(tup._tuple);
}
```

Which concludes the implementation

```c++
template <typename... Ts> struct Tuple : MakeBase<Ts...> {
  using MakeBase<Ts...>::MakeBase;
};
```
