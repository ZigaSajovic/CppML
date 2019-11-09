# `<CppML/Vocabulary/List.hpp>`

#### Table of Contents

* [`ListT`](#listt)
* [`ListA`](#lista)

## `ListT`

```c++
template <typename ...Ts>
struct ListT {};
```
### `ListT<Ts...>`

`ListT<Ts...>` represents a list of types.

## `ListA`

```c++
template <auto ...As>
struct ListA {};
```

### `ListA<As...>`

`ListT<As...>` represents a list of values.

**NOTE** 
[`ListA`](#lista) is only enabled for C++17+(more precisely, for those versions defining the `__cpp_nontype_template_parameter_auto` macro).
