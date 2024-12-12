#pragma once

#include <concepts>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::details {

template <typename T>
concept ObjectLike = requires(const T t) {
  { t.__Repr__() } -> std::same_as<Str>;
  { t.__Str__() } -> std::same_as<Str>;
  { t.__Bool__() } -> std::same_as<Bool>;
  { t.__Id__() } -> std::same_as<BigInt>;
  { static_cast<bool>(t) } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
