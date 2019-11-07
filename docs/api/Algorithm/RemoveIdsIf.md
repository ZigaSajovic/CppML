# `<CppML/Algorithm/RemoveIdsIf.hpp>`

## `RemoveIdsIf`

```c++
template <typename Predicate, typename Pipe = ml::ToList>
struct RemoveIdsIf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `RemoveIdsIf<Predicate, Pipe>`

`RemoveIdsIf<Predicate, Pipe>` is a metafunction that passes to `Pipe` a parameter pack [`ml::Int`](../Vocabulary/Value.md)`<Is>...` of indexes of the elements of the parameter pack `Ts...`, for which the predicate does not hold. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> ml::Int<Is>... -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::RemoveIdsIf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<ml::Int<0>, ml::Int<1>>>);

using T1 = ml::Invoke<
                     ml::RemoveIdsIf<
                               ml::IsClass<ml::Not<>>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<ml::Int<2>>>);
```
