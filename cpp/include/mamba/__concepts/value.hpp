#pragma once

#include <concepts>

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/__types/tuple.hpp"

namespace mamba::builtins::__concepts {

// TODO: Fix Tuple<...>
template <typename T>
concept Value =
    std::same_as<T, __types::Int> || std::same_as<T, __types::Float> ||
    std::same_as<T, __types::Bool> || std::same_as<T, __types::None>;

template <typename T>
concept EquatableValue = Value<T> && requires(const T t) {
  { t == t } -> std::same_as<bool>;
  { t != t } -> std::same_as<bool>;
};

template <typename T>
concept GreaterThanComparableValue = Value<T> && requires(const T t) {
  { t > t } -> std::same_as<bool>;
};

template <typename T>
concept LessThanComparableValue = Value<T> && requires(const T t) {
  { t < t } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::__concepts
