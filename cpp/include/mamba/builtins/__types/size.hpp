#pragma once

#include <cstdint>
#include <limits>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ `std::size_t` or Rust
/// `usize`.
using Size = std::size_t;

/// @brief The maximum value of `Size`.
constexpr Size kSizeMax = std::numeric_limits<Size>::max();

template <>
struct Traits<Size> {
  static constexpr std::string_view kName = "size";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
