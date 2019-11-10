# Tutorial

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
#### Pack expansions and non-pack parameter of alias template

[CppML](https://github.com/ZigaSajovic/CppML) **correctly** handles **mixed** alias templates of **pack** and **non-pack** arguments. This means that you can create [`metafunctions`](#metafunction) from aliases (using the [`ml::F`](./reference/Functional/F.md), from the [`Functional`](./reference/index.md#functional) header) such as
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
