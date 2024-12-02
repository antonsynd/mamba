#pragma once

#include <concepts>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept GreaterThanComparable =
    Value<T> || requires(const T lhs, const T& rhs) {
      { lhs->__Gt__(rhs) } -> std::same_as<__types::Bool>;
    };

template <typename T>
concept GreaterThanOrEqualComparable =
    Value<T> || requires(const T lhs, const T& rhs) {
      { lhs->__Ge__(rhs) } -> std::same_as<__types::Bool>;
    };

template <typename T>
concept LessThanComparable = Value<T> || requires(const T lhs, const T& rhs) {
  { lhs->__Lt__(rhs) } -> std::same_as<__types::Bool>;
};

template <typename T>
concept LessThanOrEqualComparable =
    Value<T> || requires(const T lhs, const T& rhs) {
      { lhs->__Le__(rhs) } -> std::same_as<__types::Bool>;
    };

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
