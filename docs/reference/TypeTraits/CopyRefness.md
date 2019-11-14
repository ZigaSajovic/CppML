# `<CppML/TypeTraits/CopyRefness.hpp>`

## `CopyRefness`

```c++
template <typename Pipe = ml::Identity>
struct CopyRefness {
  template <typename From, typename To>
  using f = /* .... */;
};
```
### `CopyRefness<Pipe>`

Let `U` be the type of `From`, with reference tags removed (i.e. either `&` or `&&`). Than `CopyRefness<Pipe>` is a metafunction that passes to `Pipe` the type `T`, which is generated in one of three ways:
* `From = U => T = remove_reference<To>`
* `From = U& => T = remove_reference<To>&`
* `From = U&& => T = remove_reference<To>&&`

`Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  From, To -> T <-> Pipe
```

### Example

```c++
using T = ml::f<
                ml::CopyRefness<>,
                double&, int&&>;
static_assert( std::is_same_v<
                          T0, double&&>);
```
