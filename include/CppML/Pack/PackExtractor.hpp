/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_PACK_EXTRACTOR_HPP
#define CPPML_PACK_EXTRACTOR_HPP
#include "Get.hpp"
namespace ml {

template <typename... Ts> struct PackExtractor {
  template <typename T> using f = typename ml::Get<T::value>::template f<Ts...>;
};
} // namespace ml
#endif
