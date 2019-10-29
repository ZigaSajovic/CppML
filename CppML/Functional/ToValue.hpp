//          Copyright Žiga Sajovic, XLAB 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying https://www.boost.org/LICENSE_1_0.txt)

#ifndef CPPML_TO_VALUE_HPP
#define CPPML_TO_VALUE_HPP
#include "../Vocabulary/List.hpp"
namespace ml {
/*
 * ToValue:
 * Returns an auto list of underlying values
 */
#ifdef __cpp_nontype_template_parameter_auto
struct ToValue {
  template <typename... Ts> using f = ListA<Ts::value...>;
};
#endif
} // namespace ml
#endif
