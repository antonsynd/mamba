#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept FormattableObject = requires(const T t) {
  { t.__Format__() } -> std::same_as<__types::Str>;
};

template <typename T>
concept RepresentableObject = requires(const T t) {
  { t.__Repr__() } -> std::same_as<__types::Str>;
};

template <typename T>
concept Formattable = Value<T> || FormattableObject<T>;

template <typename T>
concept Representable = Value<T> || RepresentableObject<T>;

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
