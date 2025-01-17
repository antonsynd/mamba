#pragma once

#include <cstdint>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

using UInt = std::uint32_t;

template <>
struct Traits<UInt> {
  static constexpr std::string_view kName = "uint";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
