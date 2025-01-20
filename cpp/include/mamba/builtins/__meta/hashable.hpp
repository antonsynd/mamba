#pragma once

#include <concepts>

#include "mamba/builtins/__meta/optional.hpp"
#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"
#include "mamba/builtins/__types/size.hpp"

namespace mamba::builtins::details {

template <typename T>
concept HashableObject = IsNotOptional<T> && requires(const T t) {
  { Unwrap(t).Hash() } -> std::same_as<Size>;
};

template <typename T>
concept Hashable = IsValue<T> || HashableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
