#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__concepts {

/// @brief A type that can be converted to a Bool. For generic programming
/// with Bool().
template <typename T>
concept BoolConvertible = Value<T> || requires(const T t) {
  { t.__Bool__() } -> std::same_as<__types::Bool>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
