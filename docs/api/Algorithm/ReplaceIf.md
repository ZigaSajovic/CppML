# `<CppML/Algorithm/ReplaceIf.hpp>`

## `ReplaceIf`

```c++
template <typename Predicate, typename With, typename Pipe = ml::ToList>
struct ReplaceIf {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ReplaceIf<Predicate, With, Pipe>`

`ReplaceIf<Predicate, With, Pipe>` is a metafunction that passes to `Pipe` a parameter pack `Us...` that consists of elements of the parameter pack `Ts...`, except that the elements for which `Predicate` is true are replaced by `With`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

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
using T = ml::Invoke<
                     ml::ReplaceIf<ml::IsClass<>, double>,
                     int, char, std::string>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<int, char, double>);
```
