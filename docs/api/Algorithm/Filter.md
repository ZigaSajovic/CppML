# `<CppML/Algorithm/Filter.hpp>`

## `Filter`

```c++
template <typename Predicate, typename Pipe = ml::ToList>
struct Filter {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Filter<Predicate, Pipe>`

`Filter<Predicate, Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...` consisting of the elements of the parameter pack `Ts...`, for which the predicate holds. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> Us... -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Const.md).
```
f:: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::Filter<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<std::string>>);

using T1 = ml::Invoke<
                     ml::Filter<
                               ml::IsClass<ml::Not<>>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<int, char>>);
```
