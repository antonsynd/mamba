#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

using Int = std::int_least32_t;

template <>
struct Traits<Int> {
  static constexpr std::string_view kName = "int";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
