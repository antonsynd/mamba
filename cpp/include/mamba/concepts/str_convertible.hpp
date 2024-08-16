#pragma once

#include <concepts>

#include "mamba/types/str.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept StrConvertible = requires(const T t) {
  { t.AsStr() } -> std::same_as<types::Str>;
};

}  // namespace mamba::builtins::concepts
