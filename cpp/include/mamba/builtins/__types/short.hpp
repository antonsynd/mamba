#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A new type in Mamba corresponding to C++ short int or Rust i16.
using Short = std::int16_t;

template <>
struct Traits<Short> {
  static constexpr std::string_view kName = "short";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
