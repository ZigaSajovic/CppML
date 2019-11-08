# `<CppML/TypeTraits/IsConstructible.hpp>`

## `IsConstructible`

```c++
template <typename Pipe = ml::Identity>
struct IsConstructible {
template<typename T, typename ...Args>
  using f = /* .... */;
};
```
### `IsConstructible<Pipe>`

Than `IsConstructible<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<isConstructible>`, where `isConstructible` is a `bool` marking whether `T` is constructible from `Args...`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T, Args... -> ml::Bool<isConstructible> <-> Pipe
```

### Example

```c++
using T = ml::Invoke<
                ml::IsConstructible<>,
                std::string,
                ".....">;
static_assert( std::is_same_v<
                          T,
                          ml::Bool<true>>);
```

