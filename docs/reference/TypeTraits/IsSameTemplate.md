# `<CppML/TypeTraits/IsSameTemplate.hpp>`

## `IsSameTemplate`

```c++
template <typename Pipe = ml::Identity>
struct IsSameTemplate {
template<typename T, typename U>
  using f = /* .... */;
};
```
### `IsSameTemplate<Pipe>`

Than `IsSameTemplate<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<isSameTemplate>`, where `isSameTemplate` is a `bool` marking whether `T<Args0...>` is a (possibly different) instantiation of the same template as type  `U<Args1...>` (i.e. if `T` is the same template as `U`, ignoring equality of `Args0...` and `Args1...`). `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T, U -> ml::Bool<isSameTemplate> <-> Pipe
```

### Example

```c++
using T = ml::f<
                ml::IsSameTemplate<>,
                std::vector<int>,
                std::vector<bool>>;
static_assert( std::is_same_v<
                          T,
                          ml::Bool<true>>);
```

