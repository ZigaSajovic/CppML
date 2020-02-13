# `<CppML/Algorithm/FindIdIfNot.hpp>`

## `FindIdIfNot`

```c++
template <typename Predicate, typename Pipe = ml::Identity>
struct FindIdIfNot {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `FindIdIfNot<Predicate, Pipe>`

`FindIdIfNot<Predicate, Pipe>` is a metafunction that passes to `Pipe` the index [`ml::Int`](../Vocabulary/Value.md)`<index>` of the first element of the parameter pack `Ts...`, for which the predicate does not holds. `Pipe` defaults to [`ml::Identity`](../Functional/Identity.md).

```c++
f:: Ts... -> ml::Int<index> >-> Pipe
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::f<
                 ml::FindIdIfNot<ml::IsClass<>>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<
                  T, ml::Int<0>>);

using T1 = ml::f<
                 ml::FindIdIfNot<
                           ml::IsClass<ml::Not<>>>,
                 int, char, std::string>;
static_assert(
              std::is_same_v<
                  T, ml::Int<2>>);
```
