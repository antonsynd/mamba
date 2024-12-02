#pragma once

#include <cstddef>
#include <optional>
#include <type_traits>

#include "mamba/builtins/__concepts/reference.hpp"
#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/args.hpp"

namespace mamba::builtins::__types {

struct None {
 public:
  None() = default;

  /// @brief Implicit conversion from std::nullopt_t/std::nullptr_t
  None(std::nullopt_t) {}
  None(std::nullptr_t) {}

  /// @brief Implicit conversion to std::nullopt_t/std::nullptr_t
  constexpr operator std::nullopt_t() const { return std::nullopt; }

  constexpr operator std::nullptr_t() const { return nullptr; }

  /// @brief Implicit conversion to std::optional<T> and T (std::shared_ptr)
  template <__concepts::Value T>
  constexpr operator std::optional<T>() const {
    return std::nullopt;
  }

  template <__concepts::Reference T>
  constexpr operator T() const {
    return nullptr;
  }

  /// @brief (In)equality operators
  constexpr bool operator==(std::nullopt_t) const { return true; }
  constexpr bool operator!=(std::nullopt_t) const { return false; }

  constexpr bool operator==(std::nullptr_t) const { return true; }
  constexpr bool operator!=(std::nullptr_t) const { return false; }

  template <__concepts::Value T>
  bool operator==(const std::optional<T>& other) const {
    return !other;
  }

  template <__concepts::Value T>
  bool operator!=(const std::optional<T>& other) const {
    !(*this == other);
  }

  template <__concepts::Reference T>
  bool operator==(__memory::Const<T> other) const {
    return !other;
  }

  template <__concepts::Reference T>
  bool operator!=(__memory::Const<T> other) const {
    !(*this == other);
  }
};

/// @brief Constant.
constexpr None kNone;

}  // namespace mamba::builtins::__types

// Reverse (in)equality operators for commutivity
constexpr bool operator==(std::nullopt_t, mamba::builtins::__types::None) {
  return true;
}
constexpr bool operator!=(std::nullopt_t, mamba::builtins::__types::None) {
  return false;
}

constexpr bool operator==(std::nullptr_t, mamba::builtins::__types::None) {
  return true;
}
constexpr bool operator!=(std::nullptr_t, mamba::builtins::__types::None) {
  return false;
}

template <mamba::builtins::__concepts::Value T>
bool operator==(const std::optional<T>& other, mamba::builtins::__types::None) {
  return !other;
}

template <mamba::builtins::__concepts::Value T>
bool operator!=(const std::optional<T>& other, mamba::builtins::__types::None) {
  return !!other;
}

template <mamba::builtins::__concepts::Reference T>
bool operator==(mamba::builtins::__memory::Const<T> other,
                mamba::builtins::__types::None) {
  return !other;
}

template <mamba::builtins::__concepts::Reference T>
bool operator!=(mamba::builtins::__memory::Const<T> other,
                mamba::builtins::__types::None) {
  return !!other;
}

// IWYU pragma: private
