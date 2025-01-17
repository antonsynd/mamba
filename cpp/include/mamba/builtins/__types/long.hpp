#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ long long int or Rust i64.
using Long = std::int64_t;

template <>
struct Traits<Long> {
  static constexpr std::string_view kName = "long";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
