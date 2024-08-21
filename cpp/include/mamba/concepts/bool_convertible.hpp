#pragma once

#include <concepts>

#include "mamba/types/bool.hpp"

namespace mamba::builtins::concepts {

/// @brief A type that can be converted to a Bool. For generic programming
/// with AsBool().
template <typename T>
concept BoolConvertible = requires(const T t) {
  { t.AsBool() } -> std::same_as<types::Bool>;
};

}  // namespace mamba::builtins::concepts
