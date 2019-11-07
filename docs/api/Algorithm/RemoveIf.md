# `<CppML/Algorithm/RemoveIf.hpp>`

## `RemoveIf`

```c++
template <typename Predicate, typename Pipe = ml::ToList>
struct RemoveIf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `RemoveIf<Predicate, Pipe>`

`RemoveIf<Predicate, Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...` consisting of the elements of the parameter pack `Ts...`, for which the predicate does not hold. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Us... -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Value.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::RemoveIf<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<int, char>>);

using T1 = ml::Invoke<
                     ml::RemoveIf<
                               ml::IsClass<ml::Not<>>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<std::string>>);
```
