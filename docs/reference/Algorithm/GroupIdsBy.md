# `<CppML/Algorithm/GroupIdsBy.hpp>`

## `GroupIdsBy`

```c++
template <typename By, typename Pipe = ml::ToList>
struct GroupIdsBy {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `GroupIdsBy<By, Pipe>`

`GroupIdsBy<By, Pipe>` is a metafunction that passes to `Pipe` a parameter pack [`ml::ListT`](../Vocabulary/List.md)`<ml::Int<Is>...>...`, where each list in it consists of [`ml::Int`](../Vocabulary/Value.md)`<Is>...`, indexes of types which evaluate to the same type when mapped by `By`. Formally speaking, `GroupIdsBy<By, Pipe>` forms (indexes of) equivalence classes of `Ts...` under `By`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: Ts... -> ml::ListT<ml::Int<Is>...>... >-> Pipe
```

#### By

By can be any metafunction returning a single type.
```
f:: T -> U
```

### Example

```c++
using T0 = ml::f<
                 ml::GroupIdsBy<ml::AlignmentOf<>>,
                 int, char, float, bool, double>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::ListT<ml::Int<1>, ml::Int<3>>,
                      ml::ListT<ml::Int<0>, ml::Int<2>>,
                      ml::ListT<ml::Int<4>>>);
```
