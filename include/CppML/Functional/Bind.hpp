//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_BIND_HPP
#define CPPML_BIND_HPP
#include "../Pack/Insert.hpp"
#include "Compose.hpp"
#include "Partial.hpp"

namespace ml {
/*
 * # Par:
 * Is a parameter holder for ml::Bind.
 */
template <int I, typename T> struct Par {
  template <typename Pipe> using f = ml::Insert<I, T, Pipe>;
};

/*
 * # Bind:
 * Binds arguments, creating a partially evaluated metafunction
 * **NOTE** that Is must be in sorted order
 */
template <typename F, typename... Ts> struct Bind;
template <typename F, int... Is, typename... Args>
struct Bind<F, Par<Is, Args>...>
    : ml::Invoke<ml::Compose<Par<Is, Args>...>, F> {};

/*
 * Below are a few optimizations to avoid work. When we are binding
 * successive parameters, from the first forward, it is the same as
 * if we used ml::Partial, which is more efficient.
 */
template <typename F, typename T0>
struct Bind<F, Par<0, T0>> : ml::Partial<F, T0> {};

template <typename F, typename T0, typename T1>
struct Bind<F, Par<0, T0>, Par<1, T1>> : ml::Partial<F, T0, T1> {};

template <typename F, typename T0, typename T1, typename T2>
struct Bind<F, Par<0, T0>, Par<1, T1>, Par<2, T2>>
    : ml::Partial<F, T0, T1, T2> {};

template <typename F, typename T0, typename T1, typename T2, typename T3>
struct Bind<F, Par<0, T0>, Par<1, T1>, Par<2, T2>, Par<3, T3>>
    : ml::Partial<F, T0, T1, T2, T3> {};

template <typename F, typename T0, typename T1, typename T2, typename T3,
          typename T4>
struct Bind<F, Par<0, T0>, Par<1, T1>, Par<2, T2>, Par<3, T3>, Par<4, T4>>
    : ml::Partial<F, T0, T1, T2, T3, T4> {};

template <typename F, typename T0, typename T1, typename T2, typename T3,
          typename T4, typename T5>
struct Bind<F, Par<0, T0>, Par<1, T1>, Par<2, T2>, Par<3, T3>, Par<4, T4>,
            Par<5, T5>> : ml::Partial<F, T0, T1, T2, T3, T4, T5> {};
/*
 * # _pi:
 */
template <typename T> using _p0 = Par<0, T>;
template <typename T> using _p1 = Par<1, T>;
template <typename T> using _p2 = Par<2, T>;
template <typename T> using _p3 = Par<3, T>;
template <typename T> using _p4 = Par<4, T>;
template <typename T> using _p5 = Par<5, T>;
template <typename T> using _p6 = Par<6, T>;
template <typename T> using _p7 = Par<7, T>;
template <typename T> using _p8 = Par<8, T>;
template <typename T> using _p9 = Par<9, T>;
template <typename T> using _p10 = Par<10, T>;
template <typename T> using _p11 = Par<11, T>;
template <typename T> using _p12 = Par<12, T>;
template <typename T> using _p13 = Par<13, T>;
template <typename T> using _p14 = Par<14, T>;
template <typename T> using _p15 = Par<15, T>;
template <typename T> using _p16 = Par<16, T>;
template <typename T> using _p17 = Par<17, T>;
template <typename T> using _p18 = Par<18, T>;
template <typename T> using _p19 = Par<19, T>;
template <typename T> using _p20 = Par<20, T>;
} // namespace ml
#endif
