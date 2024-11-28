#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

/// @brief A type that can be converted to a Str. For generic programming
/// with AsStr().
template <typename T>
concept StrConvertible = Value<T> || requires(const T t) {
  { t.__Str__() } -> std::same_as<__types::Str>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
