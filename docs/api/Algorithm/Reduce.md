# `<CppML/Algorithm/Reduce.hpp>`

## `Reduce`

```c++
template <typename F, typename Pipe = ml::Identity>
struct Reduce {
  template <typename Init, typename ...Ts>
  using f = /* .... */;
};
```
### `Reduce<F, Pipe>`

`Reduce<F, Pipe>` is a metafunction that passes to `Pipe` the generalized sum (with `F` taking the role of the binary operator) of `Ts...`, initialized by `Init`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Init, Ts... -> F( ... F(F(Init, T0), T1), ... Tn) -> ResultOf(Pipe)
```

#### F
F is to be a metafunction from two types, to one.
```
f:: Init, T -> Init
```

### Example

We implement [`ml::CountIf`](./CountIf.md)[`<ml::IsClass>`](../TypeTraits/IsClass.md) using `Reduce`.

```c++
using T = ml::Invoke<
    ml::Reduce<
      ml::ProductMap<                     // Construct binary function F:
          ml::Identity,                   // Map first element (Init in F) by identity
          ml::IsClass<>,                  // Map second element (T in F) by IsClass     
          ml::Add<>>>,                    // And pipe to Add
    ml::Int<0>,                           // Init
    int, std::string, bool, std::string>; // Ts...

static_assert(
              std::is_same_v<
                  T,
                  ml::Int<2>>);
```

**NOTE** that

```c++
ml::ProductMap<    // Construct binary function F:
    ml::Identity,  // Map first element (Init in F) by identity
    ml::IsClass<>, // Map second element (T in F) by IsClass     
    ml::Add<>>>,   // And pipe to Add

```

is a metafunction of type

```c++
f:: Init, T -> Identity(Init), IsClass(T) -> Init
```
which conforms to [`F`](#f). See [`ProductMap`](../Functional/ProductMap.md).

