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

template <typename T>
concept BoolConvertibleObject = requires(const T t) {
  { t.__Bool__() } -> std::same_as<__types::Bool>;
};

template <typename T>
concept BytesConvertibleObject = requires(const T t) {
  { t.__Bytes__() } -> std::same_as<__types::Bytes>;
};

template <typename T>
concept ComplexConvertibleObject = requires(const T t) {
  { t.__Complex__() } -> std::same_as<__types::Complex>;
};

template <typename T>
concept FloatConvertibleObject = requires(const T t) {
  { t.__Float__() } -> std::same_as<__types::Float>;
};

template <typename T>
concept IntConvertibleObject = requires(const T t) {
  { t.__Int__() } -> std::same_as<__types::Int>;
};

template <typename T>
concept StrConvertibleObject = requires(const T t) {
  { t.__Str__() } -> std::same_as<__types::Str>;
};

/// @brief A type that can be converted to a Bool. For generic programming
/// with Bool().
template <typename T>
concept BoolConvertible = Value<T> || BoolConvertibleObject<T>;

template <typename T>
concept BytesConvertible = Value<T> || BytesConvertibleObject<T>;

template <typename T>
concept ComplexConvertible = Value<T> || ComplexConvertibleObject<T>;

template <typename T>
concept FloatConvertible = Value<T> || FloatConvertibleObject<T>;

template <typename T>
concept IntConvertible = Value<T> || IntConvertibleObject<T>;

template <typename T>
concept StrConvertible = Value<T> || StrConvertibleObject<T>;

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
