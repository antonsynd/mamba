#pragma once

#include <concepts>
#include <type_traits>

#include "mamba/concepts/str_convertible.hpp"
#include "mamba/concepts/value.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Object = !Value<T> && requires(const T t) {
  { t.Repr() } -> std::same_as<types::Str>;
};

template <typename T>
concept EquatableObject = Object<T> && requires(const T t) {
  { t.Eq(t) } -> std::same_as<types::Bool>;
};

template <typename T>
concept GreaterThanComparableObject = Object<T> && requires(const T t) {
  { t.Lt(t) } -> std::same_as<types::Bool>;
};

template <typename T>
concept LessThanComparableObject = Object<T> && requires(const T t) {
  { t.Lt(t) } -> std::same_as<types::Bool>;
};

}  // namespace mamba::builtins::concepts
