#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ size_t or Rust usize.
using Size = std::size_t;

template <>
struct Traits<Size> {
  static constexpr std::string_view kName = "size";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
