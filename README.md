# CppML

A Meta Language for C++

**CppML** is a meta language I use when developing libraries. It was designed to allow seamless transitions between *templates*, *metafunctions* and *composable variadic transformations* they afford us. As such, metafunctions are *first-class citizens* in **CppML**, with support for features like *partial evaluation* and *pipe chaining*, usually operating on parameter packs and type-lists.
See [Examples](#examples) bellow for a demonstration of
[basic](#generate-a-list-of-tagged-elements-from-a-parameter-pack)
and
[advance](#creating-a-linear-hierarchy-of-policy-classes-from-a-flat-parameter-pack)
usage.

Note that it is an evolving project, that grows in parallel with the work I do.
Metaprogramming in C++ offers a unique experience, as one can implement **monads** and **functors**, while controlling how the resulting types are *mapped onto hardware*.

### 3 Design principles

**Idiomacy**: we view templates as *functors* that map objects of the **C++** category. As such we try to be idiomatic with respect to category theory.

**Performance**: we instantiate *as few types as possible*, which is in direct correlation with compilation speed. This leads to few design choices, such as using transparent aliases in meta-computations where-ever possible , as they do not instantiate types.

**Composability**: we design all *meta-objects* to be composable, through pipe chaining.

## Outline

A MetaFunction in **CppML** is a *template struct* with a *template alias* `f`. Most MetaFunctions have a *template parameter* `Pipe`, into which the result of its invocation is piped (think Bash pipes). Note that Pipe either defaults to `ml::Identity` (i.e. it effectively returns the result of `f`) or it defaults to `ml::ListT`(i.e. it returns the resulting parameter pack in a list of types).

This roughly translates into the following:

```c++
template <typename PossibleArg_i,     // could be 0 or more of them, depends on the
                                      // metafunction
          typename Pipe = ml::ToList> // default Pipe is to wrap the parameter
                                      // pack in a type list
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

In this section we provide two demonstrations of metaprogramming using **CppML**. In the [first](#generate-a-list-of-tagged-elements-from-a-parameter-pack) example we will first create a *tagged element list*, which will demonstrate basic functionality and working with lists. In the [second](#creating-a-linear-hierarchy-of-policy-classes-from-a-flat-parameter-pack) example, we will design a metaprogram for creating *linear CRTP hierarchies of Policy Classes from flat parameter packs*, which will demonstrate more advance notions of metaprogramming in **CppML**, such as variadic compositions of partial evaluations. Note that both examples are taken from real-life usage of the author.

### Generate a list of Tagged Elements from a parameter pack

Using **CppML** one can easily manipulate types and compose them into complex metaprograms. To demonstrate, we will take types `int`, `double` and `char`, and wrap each of them in a template `Element`, than Tag each of them with an index (similarly how `std::tuple`s elements are tagged to make them unique).

First we wrap each of them in `Element`.

```c++
template <typename> struct Element {};

using ElementList = ml::Invoke< // Invoke the metafunction that follows
    ml::Apply<                  // Apply the metafunction to all arguments
        ml::WrapIn<             // Wrap the input type
            Element>>,          // In the Element
    int, double, char>;         // Arguments to Invoke Apply on.

using U = ml::ListT<
  Element<int>,
  Element<double>,
  Element<char>>;

static_assert(std::is_same_v<ElementList, U>);
```

By `static_assert`, we see what the result is. Next, we tag each `Element`, by zipping them in a `Tag`, alongside their index.

```c++
template <class, class> struct Tag {};

using TaggedElements =
    ml::Invoke<ml::ZipWith<Tag>, // Zip the following two list with Tag
               ml::InvokeA<ml::TypeRange<>, 0, 3>, // Create a list of
                                                   // ml::Int<i>
               ElementList>;                       // List of elements

using U2 = ml::ListT<Tag<ml::Int<0>, Element<int>>,
                     Tag<ml::Int<1>, Element<double>>,
                     Tag<ml::Int<2>, Element<char>>>;

static_assert(std::is_same_v<TaggedElements, U2>);
```
Again, we observe the correct result using `static_assert`.

The reader could continue by writing a metaprogram that **permutes** the `Element`s in such a way, that their layout in memory would minimize the size of the object holding them (think of a tuple). Or, if the types wrapped by `Element` were classes, he/she could enforce a partial ordering on the list, as dictated by their *inheritance hierarchy*.

### Creating a linear hierarchy of Policy classes from a flat parameter pack

In this section we demonstrate more advance notions of metaprogramming in **CppML**, such as variadic compositions of partial evaluations.
Suppose we have a collection of policy classes of the form:

```c++
template <typename Derived, typename Tail>
struct Policy0 : Tail {
  /* Implementation */
};
```
This is used in *Policy Based Design*, where a user can specify a variadic collection of policies, which endow his class with additional functionality he selects.

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
using MakeBase = ml::Apply< // Apply the
    PartialEvaluator,  // partial evaluator on Class on the paramter pack of
                       // metafunction that follow
    ml::F<ml::Compose> // and pipe the result to the Compose metafunction, which
                       // will compose all the metafunctions in the resulting
                       // parameter pack
    >::template f<ml::F<Policies>...>; // Turn each policy into a metafunction
                                       // before passing it to the Apply
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

The above code can be cleaned up, and be made ready for general use. We write a `PrePartialEvaluator` that will Partially evaluate on arbitrary arguments, and `CRTPLinearHierarchy`, which will create the linear hierarchy for an arbitrary `Derived` type, with arbitrary `Policies`.

```c++
template <typename... Args>
using PrePartialEvaluator = ml::Partial< // Partially evaluate
    ml::F<ml::PrePartial>, // the metafunction created from PrePartial
    Args...>;

template <typename Derived> struct CRTPLinearHierarchy {
  template <class... PolicyMetafunctions>
  using f = typename ml::Apply<     // Apply the
      PrePartialEvaluator<Derived>, // partial evaluator on Derived on the
                                    // paramter pack of metafunctions
      ml::F<ml::Compose> // and pipe the result to the Compose metafunction,
                         // which will compose all the metafunctions in the
                         // resulting parameter pack
      >::template f<PolicyMetafunctions...>;
};
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
