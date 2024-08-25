#pragma once

#include <concepts>
#include <type_traits>

#include "mamba/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

/// @brief An object is anything that is not a pure value type.
/// @see mamba/__types/object.hpp
template <typename T>
concept Object = !Value<T>;

template <typename T>
concept EquatableObject = Object<T> && requires(const T t) {
  { t.Eq(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept GreaterThanComparableObject = Object<T> && requires(const T t) {
  { t.Gt(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept LessThanComparableObject = Object<T> && requires(const T t) {
  { t.Lt(t) } -> std::same_as<__types::Bool>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
