#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::details {

template <typename T>
concept GreaterThanComparableObject = requires(const T lhs, const T& rhs) {
  { lhs.__Gt__(rhs) } -> std::same_as<Bool>;
};

template <typename T>
concept GreaterThanOrEqualComparableObject =
    requires(const T lhs, const T& rhs) {
      { lhs.__Ge__(rhs) } -> std::same_as<Bool>;
    };

template <typename T>
concept LessThanComparableObject = requires(const T lhs, const T& rhs) {
  { lhs.__Lt__(rhs) } -> std::same_as<Bool>;
};

template <typename T>
concept LessThanOrEqualComparableObject = requires(const T lhs, const T& rhs) {
  { lhs.__Le__(rhs) } -> std::same_as<Bool>;
};

template <typename T>
concept GreaterThanComparable = Value<T> || GreaterThanComparableObject<T>;

template <typename T>
concept GreaterThanOrEqualComparable =
    Value<T> || GreaterThanOrEqualComparableObject<T>;

template <typename T>
concept LessThanComparable = Value<T> || LessThanComparableObject<T>;

template <typename T>
concept LessThanOrEqualComparable =
    Value<T> || LessThanOrEqualComparableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
