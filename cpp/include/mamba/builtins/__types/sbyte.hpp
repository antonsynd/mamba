#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba for an signed 8-bit integer.
using SByte = std::int8_t;

template <>
struct Traits<SByte> {
  static constexpr std::string_view kName = "sbyte";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
