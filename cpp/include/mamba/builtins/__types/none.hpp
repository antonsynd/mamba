#pragma once

#include <optional>
#include <string_view>
#include <type_traits>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

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

template <>
struct Traits<None> {
  static constexpr std::string_view kName = "None";
};

}  // namespace mamba::builtins::details

// Reverse (in)equality operators for commutivity
constexpr inline bool operator==(std::nullopt_t,
                                 mamba::builtins::details::None) {
  return true;
}
constexpr inline bool operator!=(std::nullopt_t,
                                 mamba::builtins::details::None) {
  return false;
}

template <typename T>
bool operator==(const std::optional<T>& other, mamba::builtins::details::None) {
  return !other;
}

template <typename T>
bool operator!=(const std::optional<T>& other, mamba::builtins::details::None) {
  return !!other;
}

// IWYU pragma: private
