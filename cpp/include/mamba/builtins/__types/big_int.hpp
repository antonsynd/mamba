#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ long int or Rust i64.
using BigInt = std::int_least64_t;

template <>
struct Traits<BigInt> {
  static constexpr std::string_view kName = "bigint";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
