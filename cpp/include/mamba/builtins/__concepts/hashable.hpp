#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::details {

template <typename T>
concept HashableObject = requires(const T t) {
  { t.__Hash__() } -> std::same_as<Int>;
};

template <typename T>
concept Hashable = Value<T> || HashableObject<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
