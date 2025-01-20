#pragma once

#include <concepts>

#include "mamba/builtins/__meta/optional.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

template <typename T>
concept GreaterThanComparable =
    IsNotOptional<T> && requires(const T lhs, const T rhs) {
      { Unwrap(lhs) > Unwrap(rhs) } -> std::same_as<bool>;
    };

template <typename T>
concept GreaterThanOrEqualComparable =
    IsNotOptional<T> && requires(const T lhs, const T rhs) {
      { Unwrap(lhs) >= Unwrap(rhs) } -> std::same_as<bool>;
    };

template <typename T>
concept LessThanComparable =
    IsNotOptional<T> && requires(const T lhs, const T rhs) {
      { Unwrap(lhs) < Unwrap(rhs) } -> std::same_as<bool>;
    };

template <typename T>
concept LessThanOrEqualComparable =
    IsNotOptional<T> && requires(const T lhs, const T rhs) {
      { Unwrap(lhs) <= Unwrap(rhs) } -> std::same_as<bool>;
    };

}  // namespace mamba::builtins::details

// IWYU pragma: private
