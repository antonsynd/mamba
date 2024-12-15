#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

#if __cplusplus >= 202302L
using Float = std::float32_t;
#else   // __cplusplus >= 202302L
using Float = float;
#endif  // __cplusplus >= 202302L

template <>
struct Traits<Float> {
  static constexpr std::string_view kName = "float";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
