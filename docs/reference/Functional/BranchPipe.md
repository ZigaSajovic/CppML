# `<CppML/Functional/BranchPipe.hpp>`

## `BranchPipe`

```c++
template <typename Predicate, typename IfPipe, typename ElsePipe>
struct BranchPipe {
  template <typename... Ts>
  using f = /* .... */;
};
```
### `BranchPipe<Predicate, IfPipe, ElsePipe>`

`BranchPipe<Predicate, IfPipe, ElsePipe>` is a metafunction that passes to the parameter pack `Ts...` to either `IfPipe` or `ElsePipe`, depending on the evaluation of `Predicate` on `Ts...`.

```c++
f:: Ts... -> Ts... >-> (Predicate(Ts...) ? IfPipe : ElsePipe)
```

### Example

```c++
template <typename Object>
struct Baser : Object {};

template <typename Object>
struct Holder : {
  Object object;
};

using U = ml::f<
              BranchPipe<
                    ml::IsClass<>,
                    ml::F<Baser>,
                    ml::F<Holder>>,
              int,
              string;

static_assert(
          std::is_same_v<
                         U,
                         ml::ListT<
                              Holder<int>, Baser<string>>>);
```



