# `<CppML/TypeTraits/IsClass.hpp>`

## `IsClass`

```c++
template <typename Pipe = ml::Identity>
struct IsClass {
template<typename T>
  using f = /* .... */;
};
```
### `IsClass<Pipe>`

Than `IsClass<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<isClass>`, where `isClass` is a `bool` marking whether `T` is a class type. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  T -> ml::Bool<isClass> <-> Pipe
```

### Example

```c++
using T = ml::Invoke<
                ml::IsClass<>,
                double>;
static_assert( std::is_same_v<
                          T,
                          ml::Bool<false>>);
```
