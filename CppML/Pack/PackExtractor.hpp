//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_PACK_EXTRACTOR_HPP
#define CPPML_PACK_EXTRACTOR_HPP
#include "Get.hpp"
namespace ml {

template <typename... Ts> struct PackExtractor {
  template <typename T> using f = typename ml::Get<T::value>::template f<Ts...>;
};
} // namespace ml
#endif
