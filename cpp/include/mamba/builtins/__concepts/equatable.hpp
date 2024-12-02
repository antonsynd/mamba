#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Equatable = Value<T> || requires(const T lhs, const T& rhs) {
  { lhs->__Eq__(rhs) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept Inequatable = Value<T> || requires(const T lhs, const T& rhs) {
  { lhs->__Ne__(rhs) } -> std::same_as<__types::Bool>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
