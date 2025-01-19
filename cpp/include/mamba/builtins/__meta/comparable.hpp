#pragma once

#include <concepts>

#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

template <typename T>
concept Equatable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) == Unwrap(rhs) } -> std::same_as<bool>;
};

template <typename T>
concept Inequatable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) != Unwrap(rhs) } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
