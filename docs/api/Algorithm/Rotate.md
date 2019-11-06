# `<CppML/Algorithm/Rotate.hpp>`

## `Rotate`

```c++
template <int First, int Middel, int Last, typename Pipe = ml::ToList>
struct Rotate {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `Rotate<First, Middle, Last, Pipe>`

`Rotate<First, Middle, Last, Pipe>` is a metafunction that passes to `Pipe` the parameter pack `Us...` which is the parameter pack `Ts...` which was been rotated around the `Middle`-th element. This makes `Middle`-th element the first element in `Us...`. `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f:: First ... Middle ... Last -> Middle ... Last, First .... -> ResultOf(Pipe)
```


### Example

```c++
using T = ml::Invoke<
                     ml::Rotate<1, 3, 4>,
                     ml::Int<0>, ml::Int<1>, ml::Int<2>, ml::Int<3>>;
static_assert(
              std::is_same_v<
                  T,
                  ml::ListT<
                      ml::Int<0>, ml::Int<3>, ml::Int<1>, ml::Int<2>>);
```
