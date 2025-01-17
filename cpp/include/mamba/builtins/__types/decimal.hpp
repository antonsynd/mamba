#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

#if __cplusplus >= 202302L
using Decimal = std::float128_t;
#else   // __cplusplus >= 202302L
using Decimal = long double;
#endif  // __cplusplus >= 202302L

template <>
struct Traits<Decimal> {
  static constexpr std::string_view kName = "decimal";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
