#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

template <typename T>
concept Optional =
    // Recursively unwrap T if it is wrapped in `std::shared_ptr`
    Optional<Unwrapped<T>> ||
    // Must be `std::optional<T>`
    (requires { typename T::value_type; } &&
     std::is_same_v<std::decay_t<T>, std::optional<typename T::value_type>>);

}  // namespace mamba::builtins::details

// IWYU pragma: private
