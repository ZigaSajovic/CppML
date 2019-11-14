# `<CppML/Algorithm/GroupBy.hpp>`

## `GroupBy`

```c++
template <typename By, typename Pipe = ml::ToList>
struct GroupBy {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `GroupBy<By, Pipe>`

`GroupBy<By, Pipe>` is a metafunction that passes to `Pipe` a parameter pack [`ml::ListT`](../Vocabulary/List.md)`<Us...>...`, where each list in it consists of `Us...`, types which evaluate to the same type when mapped by `By`. Formally speaking, `GroupBy<By, Pipe>` forms equivalence classes of `Ts...` under `By`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> ml::ListT<Us...>... >-> Pipe
```

#### By

By can be any metafunction returning a single type.
```
f:: T -> U
```

### Example

```c++
using T0 = ml::f<
                 ml::GroupBy<ml::AlignmentOf<>>,
                 int, char, float, bool, double>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::ListT<char, bool>,
                      ml::ListT<int, float>,
                      ml::ListT<double>>);
```
