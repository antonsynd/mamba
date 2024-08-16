#pragma once

#include <concepts>

#include "mamba/types/bool.hpp"
#include "mamba/types/float.hpp"
#include "mamba/types/int.hpp"
#include "mamba/types/none.hpp"
#include "mamba/types/str.hpp"
#include "mamba/types/tuple.hpp"

namespace mamba::builtins::concepts {

// TODO: Fix Tuple<...>
template <typename T>
concept Value = std::same_as<T, types::Int> || std::same_as<T, types::Float> ||
                std::same_as<T, types::Bool> || std::same_as<T, types::None>;

template <typename T>
concept EquatableValue = Value<T> && requires(const T t) {
  { t == t } -> std::same_as<bool>;
  { t != t } -> std::same_as<bool>;
};

template <typename T>
concept GreaterThanComparableValue = Value<T> && requires(const T t) {
  { t < t } -> std::same_as<bool>;
};

template <typename T>
concept LessThanComparableValue = Value<T> && requires(const T t) {
  { t < t } -> std::same_as<bool>;
};

}  // namespace mamba::builtins::concepts
