# `<CppML/TypeTraits/IsSame.hpp>`

## `IsSame`

```c++
template <typename Pipe = ml::Identity>
struct IsSame {
template<typename T, typename U>
  using f = /* .... */;
};
```
### `IsSame<Pipe>`

Than `IsSame<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<isSame>`, where `isSame` is a `bool` marking whether `T` is the same type as `U`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T, U -> ml::Bool<isSame> <-> Pipe
```

### Example

```c++
using T = ml::f<
                ml::IsSame<>,
                int,
                double>;
static_assert( std::is_same_v<
                          T,
                          ml::Bool<false>>);
```

