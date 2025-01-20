#pragma once

#include <concepts>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"

namespace mamba::builtins::details {

/// @brief Concept for determining if a type is an unwrapped optional, e.g.
/// `std::optional`.
template <typename T>
concept IsUnwrappedOptional = requires {
  typename T::value_type;
} && std::is_same_v<std::decay_t<T>, std::optional<typename T::value_type>>;

/// @brief Pythonic `Optional[T]` is a `std::optional<T>` stored within an
/// `std::shared_ptr` because optional types are not value types.
template <typename T>
concept IsOptional =
    IsWrapped<T> && IsUnwrappedOptional<typename T::element_type>;

/// @brief Convenience concept for the opposite of @ref IsOptional.
template <typename T>
concept IsNotOptional = !IsOptional<T>;

template <IsValid T>
std::shared_ptr<std::optional<T>> MakeOptional(T&& t) {
  return std::make_shared(std::make_optional(std::forward<T>(t)));
}

}  // namespace mamba::builtins::details

// IWYU pragma: private
