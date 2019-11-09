# `<CppML/Vocabulary/Value.hpp>`

#### Table of Contents

* [`Value`](#value)
  * [`Bool`](#bool)
  * [`Int`](#int)

## `Value`

```c++
template <typename T, T t> struct Value {
  using type = T;
  static constexpr T value = t;
};
```
### `Value<T, t>`

`Value<T, t>` a *type-value* of type `T`, with value `t`.

## `Bool`

```c++
template <bool B> using Bool = Value<bool, B>;
```

### `Bool<B>`

`Bool<B>` represents a boolean `type-value`.

## `Int`

```c++
template <bool N> using Int = Value<int, N>;
```

### `Int<N>`

`Int<N>` represents an integer `type-value`.

