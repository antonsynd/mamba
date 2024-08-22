#pragma once

#include <concepts>

#include "mamba/concepts/handle.hpp"
#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Equatable =
    EquatableValue<T> || EquatableObject<T> || EquatableHandle<T>;
;

template <typename T>
concept GreaterThanComparable =
    GreaterThanComparableValue<T> || GreaterThanComparableObject<T> ||
    GreaterThanComparableHandle<T>;

template <typename T>
concept LessThanComparable =
    LessThanComparableValue<T> || LessThanComparableObject<T> ||
    LessThanComparableHandle<T>;
;

}  // namespace mamba::builtins::concepts
