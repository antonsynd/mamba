#pragma once

#include <optional>

namespace mamba::builtins::details {

/// @brief The Pythonic `None` type. In the Mamba implementation, it is only
/// used as the null value for `Optional[T]` types (implemented as
/// `std::optional<T>`).
using None = std::nullopt_t;

/// @brief Convenience alias for code generation, equivalent to the Pythonic
/// singleton `None`.
constexpr auto kNone = std::nullopt;

}  // namespace mamba::builtins::details

// IWYU pragma: private
