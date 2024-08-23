#pragma once

#include <concepts>

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Equatable = EquatableValue<T> || EquatableObject<T>;

template <typename T>
concept GreaterThanComparable =
    GreaterThanComparableValue<T> || GreaterThanComparableObject<T>;

template <typename T>
concept LessThanComparable =
    LessThanComparableValue<T> || LessThanComparableObject<T>;

}  // namespace mamba::builtins::concepts
