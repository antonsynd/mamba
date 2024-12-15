#pragma once

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @note This goes against the Python specification which says bool is an
/// integer. This is to ensure we can write separate builtin functions for
/// Int and Bool.
using Bool = bool;

template <>
struct Traits<Bool> {
  static constexpr std::string_view kName = "bool";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
