# `<CppML/Algorithm/FilterIds.hpp>`

## `FilterIds`

```c++
template <typename Predicate, typename Pipe = ml::ToList>
struct FilterIds {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `FilterIds<Predicate, Pipe>`

`FilterIds<Predicate, Pipe>` is a metafunction that passes to `Pipe` a parameter pack [`ml::Int`](../Vocabulary/Const.md)`<Is>...` of indexes of the elements of the parameter pack `Ts...`, for which the predicate holds. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> ml::Int<Is>... -> ResultOf(Pipe)
```

#### Predicate

Predicate must be a metafunction returning [`ml::Bool<truth_value>`](../Vocabulary/Const.md).
```
f: T -> ml::Bool<truth_value>
```

### Example

```c++
using T0 = ml::Invoke<
                     ml::FilterIds<ml::IsClass<>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<ml::Int<2>>>);

using T1 = ml::Invoke<
                     ml::FilterIds<
                               ml::IsClass<ml::Not<>>>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<ml::Int<0>, ml::Int<1>>>);
```