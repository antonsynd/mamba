#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ unsigned short int or Rust
/// u16.
using UShort = std::uint16_t;

template <>
struct Traits<UShort> {
  static constexpr std::string_view kName = "ushort";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
