# `<CppML/Pack/Range.hpp>`

## `Range`

```c++
template <typename Pipe = ml::ToList>
struct Range {
  template <int From, int To, int Step = 1>
  using f = /* .... */;
};
```
### `Range<Pipe>`

`Range<Pipe>` is a metafunction that passes to `Pipe` a parameter pack [`ml::Int`](../Vocabulary/Value.md)`<Is>...`, where `Is` are `int`s in the range `[From, To)`, with arithmetic step of `Step` (which defaults to `1`). `Pipe` defaults to [`ml::ToList`](../Functional/ToList.md).

```c++
f::  int From, int To, int Step ->  ml::Int<Is>... <-> Pipe
```

**NOTE**

The range `[From, To)` is half-open; i.e. it does not include `To`.

### Example

```c++
using T0 = ml::Range::f<0, 6, 2>;
static_assert( std::is_same_v<
                          T0,
                          ml::ListT<
                            ml::Int<0>, ml::Int<2>, ml::Int<4>>>);

using T1 = ml::Range::f<6, 0, -2>;
static_assert( std::is_same_v<
                          T0,
                          ml::ListT<
                            ml::Int<6>, ml::Int<4>, ml::Int<2>>>);
```
