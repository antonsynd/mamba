#pragma once

#include <concepts>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept ObjectLike = requires(const T t, const __types::Object* obj) {
  { t.__Repr__() } -> std::same_as<__types::Str>;
  { t.__Str__() } -> std::same_as<__types::Str>;
  { t.__Bool__() } -> std::same_as<__types::Bool>;
  { t.__Id__() } -> std::same_as<__types::BigInt>;
  { static_cast<bool>(t) } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
