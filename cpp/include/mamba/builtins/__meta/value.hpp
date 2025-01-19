#pragma once

#include <concepts>
#include <optional>
#include <type_traits>

#include "mamba/builtins/__types/forward_declarations.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins::details {

/// @brief All arithmetic types, `bool`, `Bool`, `Complex`, and `None` are
/// value types.
template <typename T>
concept IsValue =
    std::is_arithmetic_v<T> || std::same_as<std::decay_t<T>, Bool> ||
    std::same_as<std::decay_t<T>, Complex> ||
    std::same_as<std::decay_t<T>, None>;

template <typename T>
concept IsNotValue = !IsValue<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
