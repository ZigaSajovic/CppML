# `<CppML/Functional/Identity.hpp>`

## `Identity`

```c++
struct Identity {
  template <typename T>
  using f = /* .... */;
};
```
### `Identity`

`Identity` evaluates to the type it was passed.
```c++
f:: T -> T
```

### Example

If we want the result of the metacomputation to be `Pipe`-ed into a `std::tuple`, we can transform it into a metafunction, and use it as `Pipe`.

```c++
using T = ml::Invoke<
              ml::Identity,
              int>;
static_assert(
        std::is_same_v<
              int, T>);
```
