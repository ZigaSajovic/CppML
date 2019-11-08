# `<CppML/TypeTraits/IsConvertible.hpp>`

## `IsConvertible`

```c++
template <typename Pipe = ml::Identity>
struct IsConvertible {
template<typename From, typename To>
  using f = /* .... */;
};
```
### `IsConvertible<Pipe>`

Than `IsConvertible<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<isConvertible>`, where `isConvertible` is a `bool` marking whether `From` can be converted to `To`. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  From, To -> ml::Bool<isConvertible> <-> Pipe
```

### Example

```c++
using T = ml::Invoke<
                ml::IsConvertible<>,
                int[],
                int*>;
static_assert( std::is_same_v<
                          T,
                          ml::Bool<true>>);
```

