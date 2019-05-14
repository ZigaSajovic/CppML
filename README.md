# CppML

A composable Meta Language for C++

**CppML** is a meta language I use when developing libraries. It comes equipped with various metafunctions, that are building blocks for writing metaprograms.

Note that it is an evolving project, that grows in parallel with the work I do.

## Outline

A MetaFunction in **CppML** is a *template struct* with a *template alias* `f`. Each MetaFunction has a *template parameter* `Pipe`, into which the result of its invocation is piped (think Bash pipes). Note that Pipe usually defaults to `ml::ListT`, meaning it return a list of types.

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
Note that we have omitted possible details, which can be observed in implementations.
These metafunctions can be conveniently invoked by (assuming existence of  types `U`, `T1`, `T2`, `T2`)
```c++
using Result =
        ml::Invoke< // invokes the specified metafunction (f alias)
            MetaFunction<U>, T1, T2, T3>; // on these parameters
```

### Example: Generate a list of Tagged Elements from a parameter pack

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
template <class ...> struct Tag {};

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

#### Going further

The reader could continue by writing a metaprogram that **permutes** the `Element`s in such a way, that their layout in memory would minimize the size of the object holding them (think of a tuple). Or, if the types wrapped by `Element` were classes, he/she could enforce a partial ordering on the list, as dictated by their *inheritance hierarchy*.
