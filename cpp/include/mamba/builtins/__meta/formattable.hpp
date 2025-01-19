#pragma once

#include <concepts>

#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::details {

template <typename T>
concept FormattableObject = requires(const T t) {
  { Unwrap(t).Format() } -> std::same_as<Str>;
};

template <typename T>
concept Formattable = IsValue<T> || FormattableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
