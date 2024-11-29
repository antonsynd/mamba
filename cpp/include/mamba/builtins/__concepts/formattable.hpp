#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Formattable = Value<T> || requires(const T t) {
  { t.__Format__() } -> std::same_as<__types::Str>;
};

template <typename T>
concept Representable = Value<T> || requires(const T t) {
  { t.__Repr__() } -> std::same_as<__types::Str>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
