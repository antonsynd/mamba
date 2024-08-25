#pragma once

#include <concepts>

#include "mamba/__concepts/object.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

/// @brief A type that can be converted to a Str. For generic programming
/// with AsStr().
template <typename T>
concept StrConvertibleObject = Object<T> && requires(const T t) {
  { t.AsStr() } -> std::same_as<__types::Str>;
};

}  // namespace mamba::builtins::__concepts
