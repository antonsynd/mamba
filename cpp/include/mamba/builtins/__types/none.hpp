#pragma once

#include <cstddef>
#include <optional>
#include <type_traits>

#include "mamba/__concepts/value.hpp"

namespace mamba::builtins::__types {

/// @brief Templated None type.
template <typename T>
using None =
    std::conditional_t<__concepts::Value<T>, std::nullopt_t, std::nullptr_t>;

namespace details {

template <typename T>
constexpr auto select_none_value() {
  if constexpr (__concepts::Value<T>) {
    return std::nullopt;
  } else {
    return nullptr;
  }
}

}  // namespace details

/// @brief Templated None constant.
template <typename T>
constexpr auto kNone = select_none_value<T>();

}  // namespace mamba::builtins::__types

// IWYU pragma: private
