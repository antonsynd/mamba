#pragma once

#include <concepts>

#include "mamba/builtins/__memory/args.hpp"

namespace mamba::builtins::details {

template <typename T>
concept GreaterThanComparable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) > Unwrap(rhs) } -> std::same_as<bool>;
};

template <typename T>
concept GreaterThanOrEqualComparable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) >= Unwrap(rhs) } -> std::same_as<bool>;
};

template <typename T>
concept LessThanComparable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) < Unwrap(rhs) } -> std::same_as<bool>;
};

template <typename T>
concept LessThanOrEqualComparable = requires(const T lhs, const T rhs) {
  { Unwrap(lhs) <= Unwrap(rhs) } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
