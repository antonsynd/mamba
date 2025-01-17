#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ unsigned long long int or
/// Rust u64.
using ULong = std::uint64_t;

template <>
struct Traits<ULong> {
  static constexpr std::string_view kName = "ulong";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
