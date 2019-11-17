/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
#ifndef CPPML_COPY_REFNESS_HPP
#define CPPML_COPY_REFNESS_HPP
#include "../Functional/Identity.hpp"
#include "../Functional/IfElse.hpp"
#include <type_traits>

namespace ml {
/*
 * CopyRefness:
 * Returns type To, with the same refness as From.
 */
template <typename Pipe = ml::Identity> struct CopyRefness {
  template <typename From, typename To>
  using f = typename Pipe::template f<
      typename Implementations::IfElse<!std::is_reference<From>::value>::
          template f<
              typename std::remove_reference<To>::type,
              typename Implementations::
                  IfElse<std::is_rvalue_reference<From>::value>::template f<
                      typename std::remove_reference<To>::type &&, To &>>>;
};
} // namespace ml
#endif
