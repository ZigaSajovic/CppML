# `<CppML/TypeTraits/IsValid.hpp>`

## `IsValid`

```c++
template <typename Pipe = ml::Identity>
struct IsValid {
template<typename F, typename ...Args>
  using f = /* .... */;
};
```
### `IsValid<Pipe>`

Than `IsValid<Pipe>` is a metafunction that passes to `Pipe` an [`ml::Bool`](../Vocabulary/Value.md)`<truthValue>`, where `truthValue` is a `bool` marking whether the metafunction `F` can be invoked with `Args...` (i.e. if the expression is not *ill-formed*, and compiles). `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f::  F, Args... -> ml::Bool<truthValue> <-> Pipe
```

### Example

It can be used to implement introspection.

```c++
template <typename _T>
using HasBracketOperator = decltype(std::declval<_T>()[0]);
using T0 = ml::Invoke<
                ml::IsValid<>,
                ml::F<HasBracketOperator>,
                std::vector<int>>;
using T1 = ml::Invoke<
                ml::IsValid<>,
                ml::F<HasBracketOperator>,
                int>;
static_assert( std::is_same_v<
                          T0, ml::Bool<true>>);
static_assert( std::is_same_v<
                          T1, ml::Bool<false>>);
```
