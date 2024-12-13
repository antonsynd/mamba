#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::details {

template <typename T>
concept InequatableObject = requires(const T lhs, const T& rhs) {
  { lhs.__Ne__(rhs) } -> std::same_as<Bool>;
};

template <typename T>
concept Inequatable = Value<T> || InequatableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
