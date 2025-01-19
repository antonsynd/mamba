#pragma once

#include <cstdint>
#include <limits>
#include <string_view>
#include <type_traits>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ `std::size_t` or Rust
/// `usize`.
using SSize = std::make_signed<std::size_t>::type;

/// @brief The maximum value of `Size`.
constexpr SSize kSSizeMax = std::numeric_limits<SSize>::max();

template <>
struct Traits<SSize> {
  static constexpr std::string_view kName = "ssize";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
