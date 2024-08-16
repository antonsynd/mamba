#pragma once

#include <concepts>

#include "mamba/types/bool.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept BoolConvertible = requires(const T t) {
  { t.AsBool() } -> std::same_as<types::Bool>;
};

}  // namespace mamba::builtins::concepts
