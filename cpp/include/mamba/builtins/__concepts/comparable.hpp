#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Equatable = Value<T> || requires(const T t) {
  { t.__Eq__(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept Inequatable = Value<T> || requires(const T t) {
  { t.__Ne__(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept GreaterThanComparable = Value<T> || requires(const T t) {
  { t.__Gt__(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept GreaterThanOrEqualComparable = Value<T> || requires(const T t) {
  { t.__Ge__(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept LessThanComparable = Value<T> || requires(const T t) {
  { t.__Lt__(t) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept LessThanOrEqualComparable = Value<T> || requires(const T t) {
  { t.__Le__(t) } -> std::same_as<__types::Bool>;
};

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
