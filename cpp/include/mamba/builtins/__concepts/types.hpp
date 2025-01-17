#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

#include "mamba/builtins/__concepts/optional.hpp"
#include "mamba/builtins/__types/value.hpp"

namespace mamba::builtins::details {

/// @brief All primitive types are value types, including None and Optional<T>
template <typename T>
concept Value =
    std::same_as<std::decay_t<T>, Byte> ||
    // std::same_as<std::decay_t<T>, Complex> ||
    std::same_as<std::decay_t<T>, Double> ||
    std::same_as<std::decay_t<T>, Float> ||
    std::same_as<std::decay_t<T>, Int> || std::same_as<std::decay_t<T>, Long> ||
    std::same_as<std::decay_t<T>, None> ||
    std::same_as<std::decay_t<T>, Short> ||
    std::same_as<std::decay_t<T>, Size> ||
    std::same_as<std::decay_t<T>, SByte> ||
    std::same_as<std::decay_t<T>, UInt> ||
    std::same_as<std::decay_t<T>, ULong> ||
    std::same_as<std::decay_t<T>, UShort> || Optional<T>;

template <typename T>
concept NotValue = !Value<T>;

/// @brief All types that should be wrapped in std::shared_ptr<T> are reference
/// types.
template <typename T>
concept Reference = requires {
  typename T::element_type;
} && std::is_same_v<std::decay_t<T>, std::shared_ptr<typename T::element_type>>;

template <typename T>
concept NotReference = !Reference<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
