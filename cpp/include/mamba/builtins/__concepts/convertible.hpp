#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/bytes.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__concepts {

/// @brief A type that can be converted to a Bool. For generic programming
/// with Bool().
template <typename T>
concept BoolConvertible = Value<T> || requires(const T t) {
  { t->__Bool__() } -> std::same_as<__types::Bool>;
};

template <typename T>
concept BytesConvertible = Value<T> || requires(const T t) {
  { t->__Bytes__() } -> std::same_as<__types::Bytes>;
};

template <typename T>
concept ComplexConvertible = Value<T> || requires(const T t) {
  { t->__Complex__() } -> std::same_as<__types::Complex>;
};

template <typename T>
concept FloatConvertible = Value<T> || requires(const T t) {
  { t->__Float__() } -> std::same_as<__types::Float>;
};

template <typename T>
concept IntConvertible = Value<T> || requires(const T t) {
  { t->__Int__() } -> std::same_as<__types::Int>;
};

/// @brief A type that can be converted to a Str. For generic programming
/// with Str().
template <typename T>
concept StrConvertible = Value<T> || requires(const T t) {
  { t.__Str__() } -> std::same_as<__types::Str>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
