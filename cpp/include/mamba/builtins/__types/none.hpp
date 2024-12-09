#pragma once

#include <optional>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins::__types {

struct None {
 public:
  None() = default;

  /// @brief Implicit conversion to std::nullopt_t
  constexpr operator std::nullopt_t() const { return std::nullopt; }

  /// @brief Implicit conversion to std::optional<T>
  template <typename T>
  constexpr operator std::optional<T>() const {
    return std::nullopt;
  }

  /// @brief (In)equality operators
  constexpr bool operator==(std::nullopt_t) const { return true; }
  constexpr bool operator!=(std::nullopt_t) const { return false; }

  constexpr bool operator==(const None&) const { return true; }
  constexpr bool operator!=(const None&) const { return false; }

  template <typename T>
  bool operator==(const std::optional<T>& other) const {
    return !other;
  }

  template <typename T>
  bool operator!=(const std::optional<T>& other) const {
    !(*this == other);
  }
};

/// @brief Constant.
constexpr None kNone;

}  // namespace mamba::builtins::__types

// Reverse (in)equality operators for commutivity
constexpr inline bool operator==(std::nullopt_t,
                                 mamba::builtins::__types::None) {
  return true;
}
constexpr inline bool operator!=(std::nullopt_t,
                                 mamba::builtins::__types::None) {
  return false;
}

template <typename T>
bool operator==(const std::optional<T>& other, mamba::builtins::__types::None) {
  return !other;
}

template <typename T>
bool operator!=(const std::optional<T>& other, mamba::builtins::__types::None) {
  return !!other;
}

// IWYU pragma: private
