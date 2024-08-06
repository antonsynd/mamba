#pragma once

#include <concepts>

#include "mamba/bool.hpp"
#include "mamba/str.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept BoolConvertible = requires(const T t) {
  { t.AsBool() } -> std::same_as<types::Bool>;
};

template <typename T>
concept StrConvertible = requires(const T t) {
  { t.AsStr() } -> std::same_as<types::Str>;
};

}  // namespace mamba::builtins::concepts
