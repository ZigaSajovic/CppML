# CppML

A Meta Language for C++

**CppML** is a meta language I use when developing libraries. It was designed to allow seamless transitions between *templates*, *metafunctions* and *composable variadic transformations* they afford us. As such, metafunctions are *first-class citizens* in **CppML**, with support for features like *partial evaluation* and *pipe chaining*, usually operating on parameter packs.

Metaprogramming in C++ offers a unique experience, as one can implement **categorical concepts** (e.g. *monads* and *functors*), while controlling how the resulting types are **mapped onto hardware**. For a detailed demonstration, consult the tutorial for how to [optimize the memory layout of std::tuple](https://github.com/ZigaSajovic/optimizing-the-memory-layout-of-std-tuple) using **CppML**.

### 3 Design principles

**Idiomacy**: we view templates as *functors* that map objects of the **C++** category. As such we try to be idiomatic with respect to category theory.

**Performance**: we instantiate *as few types as possible*, which is in direct correlation with compilation speed. This leads to few design choices, such as using transparent aliases in meta-computations where-ever possible , as they do not instantiate types.

**Composability**: we design all *meta-objects* to be composable, through pipe chaining.

## Outline

A MetaFunction in **CppML** is a *template struct* with a *template alias* `f`.
All MetaFunctions have a *template parameter* `Pipe`, into which the result of its invocation is piped (think Bash pipes). Note that Pipe either defaults to `ml::Identity` (i.e. it effectively returns the result of `f`) or it defaults to `ml::ToList`(i.e. it returns the resulting parameter pack in a list of types).

This roughly translates into the following:

```c++
template <typename PossibleArg_i,     // could be 0 or more of them, depends on the
                                      // metafunction
          typename Pipe = ml::ToList> // default Pipe is to wrap the parameter
                                      // pack in a type list (or Identity)
struct MetaFunction {
  template <typename... Args>
  using f = typename Pipe::template f< // Result of MetFunctionImplementation
                                       // Gets piped to Pipe
      MetFunctionImplementation::template f<PossibleArg_i, // PossibleArg_i could
                                                           // be used somewhere else
                                            Args...>>;
};
```
As such, the composition three metafunctions `mF1`, `mF2` and `mF3` (assuming each of them has Pipe as their only parameter) is defined by
```c++
using MF = mf1<mf2<mf3<>>>;
```
which is now a metafunction like any other, and it too is invokable through the `f` alias.
```c++
using Result = MF::template f<T1, T2 /*... Tn*/ >
```
Note that metafunctions can be conveniently invoked by using
```c++
using Result =
        ml::Invoke< // invokes the MF metafunction (f alias)
            MF, T1, T2 /*... Tn*/; // on these parameters
```
the `ml::Invoke` alias.

Note that **CppML** also possesses the mechanics needed to compose metafunctions, that do not define the convenient `Pipe` template parameter (see the [second](#creating-a-linear-hierarchy-of-policy-classes-from-a-flat-parameter-pack) example below).



## Examples


In this section we provide two demonstrations of metaprogramming using **CppML**. The [first](#generating-a-permutation-of-elements,-that-minimizes-the-needed-padding-in-a-tuple) will demonstrate a few algorithms on type-lists and how to compose actions on them. The [second](#creating-a-linear-hierarchy-of-policy-classes-from-a-flat-parameter-pack) will demonstrate notions such as variadic compositions of partial evaluations.

### Generating a permutation of elements, that minimizes the needed padding in a tuple

You can imagine `std::tuple<T0, T1, ..., Tn>` as a class, with members `T0 t0`, `T1 t1`, ..., `Tn tn`, laid out in the specified (or reversed) order. As such, like in any class, padding needs to be inserted between the members, so that they are *naturally aligned*, which generally means that the data's memory address is a multiple of the data size (have a look at the [Data structure alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)).

Our goal is two fold. We wish to **permute** the order of elements, so as to **minimize** the object **size**. But, elements need to be accessible in the same order user specified them; i.e. the element that was specified in slot `2`, must be accessible through `2`. In other words, from the users perspective, it is **as if** nothing was done.

We will achieve this by first marking each element with its starting number. Than, we will use **sorting** on the **aligment** as a heuristic solution to the packing problem.


```c++
template <typename _Tag, typename T> struct Tag : T{};

template <typename... Ts>
using PermuteAlign = ml::Invoke<
    ml::ZipWith<Tag,           // Zip the input lists with Tag and pipe into
                ml::Sort<      // sort, whith the comparator
                    ml::Map< // that Maps (the two comparing elements):
                        ml::UnList<    // remove outer Tag, and pipe into
                            ml::Get<1, // getting the second element, and pipe
                                       // into
                                    ml::AligmentOf<>>>, // computing their
                                                        // aligment
                        ml::Greater<>>>>, // than compare the generated elements
                                          // (pipe-ing from the Map)
                                          // using Greater
    typename ml::TypeRange<>::template f<0, sizeof...(Ts)>, // generate a range from
                                                            // [0, numOfTypes)
    ml::ListT<Ts...>>;

```

On a concrete example, this meta program outputs

```c++
using T1 = PermuteAlign<char, int, char, int, char, double, char>;
using List =
    ml::ListT<Tag<ml::Value<int, 5>, double>, Tag<ml::Value<int, 3>, int>,
              Tag<ml::Value<int, 1>, int>, Tag<ml::Value<int, 6>, char>,
              Tag<ml::Value<int, 4>, char>, Tag<ml::Value<int, 2>, char>,
              Tag<ml::Value<int, 0>, char>>
static_assert(
              std::is_same_v<T1, List>);
```
which can now be used to design a base class for the tuple. You can find this example explained in detail [here](https://github.com/ZigaSajovic/optimizing-the-memory-footprint-of-std-tuple).

### Creating a linear hierarchy of Policy classes from a flat parameter pack

Suppose we have a collection of policy classes of the form:

```c++
template <typename Derived, typename Tail>
struct Policy0 : Tail {
  /* Implementation */
};
```
This is used in *Policy Based Design*, where a user can specify a variadic collection of policies, which endow his class with additional functionality he selects. Note the **Derived** parameter, which serves for **CRPTP**.

To that purpose, we need a metaprogram, that takes a variadic sequence of such policies, and generates a linear hierarchy that can be used as a base class:
```c++
using WantedBase = Policy0<Class,
                           Policy1<Class,
                                   Policy2<Class,
                                       /*... Policies from 2 : n*/
                                           PolicyN<Class, Bottom>>>>;
```
This is achieved as follows:

We start with a variadic parameter pack of policy classes. First we transform each policy  into a metafunction. Than we partially evaluate each of them on `Class` (now each of them takes only one parameter, namely the `Tail`). We finish by composing all these partially evaluated metafunctions. This will result in a metafunction taking one parameter, `Bottom`, which will map it to the `WantedBase`, as above.

This will result in a `MakeBase` metaprogram, which we can use when coding the `Class` that users can customize using mentioned policies.

```c++
template <template <class, class> class ...Policies>
struct Class : MakeBase<Policies...>::template f<Bottom> {
  /* Implementation */
};
```
were `MakeBase<Policies...>::template f<Bottom>` is equivalent to `WantedBase` above. With such a metaprogram, the user will be able to instantiate the `Class` by listing the wanted policies, instead of manually nesting them
```c++
Class<Policy0, Policy1, Policy2, /* ... */ PolicyN> myInstance;
```

We will first implement the `MakeBase` metafunction for our specific case, and than generalize it to a `CRTPLinearHierarchy` that can be used in a general setting (skip to [there](#general-crtplinearhierarchy-metafunction)). Note that [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) stands for *curiously recurring template pattern*.

#### Creating the needed tools

First, we show how to transform a template into a metafunction:
```c++
using MF0 = ml::F<Policy0>;
static_assert(std::is_same_v<MF0::template f<T0, T1>, //
                             Policy0<T0, T1>>);
```
The created metafunction can be partially evaluated:
```c++
using MF0partial = ml::PrePartial<MF0, T0>;
static_assert(std::is_same_v<MF0partial::template f<T1>, //
                             Policy0<T0, T1>>);
```
We can go further, and create a metafuntion, that will take a policy metafunction like `MF0`, and partially evaluate it at `Class`. In the bellow, note that `Partial`is like `PrePartial`, but it partially evaluates the trailing arguments (where as the `PrePartial` does so for the preceding arguments).
```c++
using PartialEvaluator =
    ml::Partial<                       // Partially evaluate
                ml::F<ml::PrePartial>, // the metafunction created from PrePartial
                Class                  //  on the argument Class
                >;
```
We can now use the `PartialEvaluator` to create metafunction like `MF0partial`:
```c++
using MF0partial = ml::PrePartial<MF0, Class>;
using MF0partialMapped = PartialEvaluator::template f<MF0>;
static_assert(std::is_same_v<MF0partialMapped,
                             MF0partial>);
```
#### MakeBase metafunction

We can now write the metaprogram we described at the beginning of the section.

```c++
template <template <class...> class... Policies>
using MakeBase = ml::Map< // Map the
    PartialEvaluator,     // partial evaluator on Class on the paramter pack of
                          // metafunction that follow
    ml::F<ml::Compose> // and pipe the result to the Compose metafunction, which
                       // will compose all the metafunctions in the resulting
                       // parameter pack
    >::template f<ml::F<Policies>...>; // Turn each policy into a metafunction
                                       // before passing it to the Map
                                       // metafunction
```



As we can see, the `MakeBase` metafunction produces the desired result.

```c++
using Base = MakeBase<Policiy0,
                      Policy1,
                      Policy2,
                      /* ... */
                      PolicyN>::template f<Bottom>
static_assert(std::is_same_v<WantedBase,
                             Base>);
```

where `WantedBase` is as defined in the beginning of this section. We can now define the `Class` as specified.
```c++
template <template <class, class> class ...Policies>
struct Class : MakeBase<Policies...>::template f<Bottom> {
  /* Implementation */
};

Class<Policy0, Policy1, Policy2, /* ... */ PolicyN> myInstance;
```

### General CRTPLinearHierarchy metafunction

Now we generalize the above. We write a `PrePartialEvaluator` that will Partially evaluate on arbitrary arguments, and `CRTPLinearHierarchy`, which will create the linear hierarchy for an arbitrary `Derived` type, with arbitrary `Policies`.

```c++
template <typename... Args>
using PrePartialEvaluator = ml::Partial< // Partially evaluate
    ml::F<ml::PrePartial>, // the metafunction created from PrePartial
    Args...>;

template <typename Derived> struct CRTPLinearHierarchy {
  template <class... PolicyMetafunctions>
  using f = typename ml::Map<       // Map the paramter pack of metafunctions
      PrePartialEvaluator<Derived>, // partial evaluator on Derived on the
      ml::F<ml::Compose> // and pipe the result to the Compose metafunction,
                         // which will compose all the metafunctions in the
                         // resulting parameter pack
      >::template f<PolicyMetafunctions...>;
```
We can use the `CRTPLinearHierarchy` metafunction to reproduce `MakeBase`above. Note that we create metafunction from Policies before passing them to `CRTPLinearHierarchy` (using `ml::F`).
```c++
using Base = ml::Invoke<meta::CRTPLinearHierarchy<Class>,
                        mf::F<Policy0>, //
                        mf::F<Policy1>, //
                        /* ... */
                        mf::F<PolicyN>>::template f<Bottom>;

static_assert(std::is_same_v<WantedBase,
                             Base>);

```
The `Class` can now be implemented using the `CRTPLinearHierarchy` metafunction.
```c++
template <template <class, class> class... Policies>
struct Class : ml::Invoke<CRTPLinearHierarchy<Class>,
                          ml::F<Policies>...>::template f<Bottom> {
  /* Implementation */
};
```
