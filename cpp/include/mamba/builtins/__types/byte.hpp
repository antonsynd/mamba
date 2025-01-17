#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba for an unsigned 8-bit integer.
using Byte = std::uint8_t;

template <>
struct Traits<Byte> {
  static constexpr std::string_view kName = "byte";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
