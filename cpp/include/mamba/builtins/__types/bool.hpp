#pragma once

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A boolean.
/// @note This goes against the Python specification which says bool is an
/// integer. This is to ensure we can write overload built-in functions for
/// both Int and Bool.
using Bool = bool;

template <>
struct Traits<Bool> {
  // using delegate_type = BoolDelegate;
  static constexpr std::string_view kName = "bool";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
