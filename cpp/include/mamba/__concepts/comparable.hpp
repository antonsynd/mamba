#pragma once

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Equatable = EquatableValue<T> || EquatableObject<T>;

template <typename T>
concept GreaterThanComparable =
    GreaterThanComparableValue<T> || GreaterThanComparableObject<T>;

template <typename T>
concept LessThanComparable =
    LessThanComparableValue<T> || LessThanComparableObject<T>;

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
