#pragma once

#include <concepts>

#include "mamba/concepts/object.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins::concepts {

/// @brief A type that can be converted to a Str. For generic programming
/// with AsStr().
template <typename T>
concept StrConvertibleObject = Object<T> && requires(const T t) {
  { t.AsStr() } -> std::same_as<types::Str>;
};

}  // namespace mamba::builtins::concepts
