#pragma once

#include <concepts>

#include "mamba/__concepts/object.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__concepts {

/// @brief A type that can be converted to a Bool. For generic programming
/// with AsBool().
template <typename T>
concept BoolConvertibleObject = Object<T> && requires(const T t) {
  { t.AsBool() } -> std::same_as<__types::Bool>;
};

}  // namespace mamba::builtins::__concepts
