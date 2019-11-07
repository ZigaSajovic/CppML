# `<CppML/Functional/ToValue.hpp>`

## `ToValue`

```c++
struct ToValue {
  template <typename ...Ts>
  using f = /* .... */;
};
```
### `ToValue`

`ToValue` is a metafunction that returns the parameter pack `Ts::value...` wrapped in a list; [`ml::ListA`](../Vocabulary/List.md)`<Ts::value...>`.

```c++
f:: Ts... -> ml::ListA<Ts::value...>
```

**NOTE** that [`ToValue`](./ToValue.md) is only enabled for C++17+(more precisely, for those versions defining the `__cpp_nontype_template_parameter_auto` macro).

### Example

```c++
using T = ml::Invoke<
                ml::ToValue,
                ml::Int<0>, ml::Int<1>>;
static_assert(
        std::is_same_v<
                T,
                ml::ListA< 0, 1>>);
```
