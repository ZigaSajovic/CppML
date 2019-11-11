/**
 * Copyright Žiga Sajovic, XLAB 2019
 * Distributed under the MIT License
 *
 * https://github.com/ZigaSajovic/CppML
 **/
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
