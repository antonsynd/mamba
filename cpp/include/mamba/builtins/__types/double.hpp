#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

#if __cplusplus >= 202302L
using Double = std::float64_t;
#else   // __cplusplus >= 202302L
using Double = double;
#endif  // __cplusplus >= 202302L

template <>
struct Traits<Double> {
  static constexpr std::string_view kName = "double";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
