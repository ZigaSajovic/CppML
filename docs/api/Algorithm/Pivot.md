# `<CppML/Algorithm/Pivot.hpp>`

## `Pivot`

```c++
template <int N, typename Pipe = ml::ToList>
struct Pivot {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Pivot<N, Pipe>`

`Pivot<N, Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Us...` which is the parameter pack `Ts...` which was pivoted around `N`-th element (making `N`-th element the first element in `Us...`). `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: First ... N-th ... Last -> N-th ... Last, First .... -> ResultOf(Pipe)
```


### Example

```c++
using T = ml::Invoke<
                     ml::Pivot<2>,
                     ml::Int<0>, ml::Int<1>, ml::Int<2>, ml::Int<3>>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::Int<2>, ml::Int<3>, ml::Int<0>, ml::Int<1>>);
```
