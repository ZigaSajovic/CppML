# `<CppML/Functional/DelayedEval.hpp>`

## `DelayedEval`

```c++
template <typename F, int N, typename ...Ts>
using f = /*...*/
};
```
### `DelayedEval<F, N, Ts...>`

`DelayedEval<F, N, Ts...>` is a helper metafunction to combat the *non-varadic parameter pack used as argument for a  varadic parameter pack* compiler error. It happens when you pass a parameter pack to a template (alias) expecting 
```c++
<typename T, typename ...Ts>
```
a type and a parameter pack.

It is not meant to be used outside implementations.
