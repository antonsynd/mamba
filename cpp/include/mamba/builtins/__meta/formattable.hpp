#pragma once

#include <concepts>

#include "mamba/builtins/__meta/types.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::details {

template <typename T>
concept FormattableObject = requires(const T t) {
  { Unwrap(t).__Format__() } -> std::same_as<Str>;
};

template <typename T>
concept Formattable = Value<T> || FormattableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
