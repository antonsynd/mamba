#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Hashable = Value<T> || requires(const T t) {
  { t.__Hash__() } -> std::same_as<__types::Int>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
