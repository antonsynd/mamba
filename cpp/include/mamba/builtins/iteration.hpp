#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <__concepts::Entity T>
class IteratorWrapper;

}  // namespace details

template <__concepts::Entity T>
class Iterator : public builtins::__types::Object {
 public:
  /// @brief Mamba-specific
  using element = T;
  using self = Iterator<element>;
  using handle = __memory::handle_t<self>;

  using iterator = details::IteratorWrapper<element>;
  using value_type = __memory::managed_t<element>;

  virtual ~Iterator() = default;

  virtual __memory::handle_t<Iterator<element>> Iter() = 0;

  /// @brief Returns the next value from the iterator, starting from the first
  /// value.
  /// @code next(iterator)
  virtual value_type Next() = 0;

  /// @brief Returns false all the time for all arguments by default.
  /// @code iterator == other
  template <typename U>
  __types::Bool Eq(const U&) const {
    return false;
  }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code list == other
  template <>
  __types::Bool Eq(const self& other) const {
    return this == &other;
  }

  template <>
  __types::Bool Eq(const handle& other) const {
    return Eq(*other);
  }

  /// @brief Native support for C++ == and != operators.
  template <typename U>
  bool operator==(const U& other) const {
    return Eq(other);
  }

  template <>
  bool operator==(const handle& other) const {
    return operator==(*other);
  }

  template <typename U>
  bool operator!=(const U& other) const {
    return !Eq(other);
  }

  template <>
  bool operator!=(const handle& other) const {
    return operator!=(*other);
  }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }
};

namespace __concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->Iter() } -> std::same_as<__memory::handle_t<Iterator<U>>>;
};

template <typename T>
concept Iterable = TypedIterable<T, typename T::element>;

}  // namespace __concepts

template <__concepts::Entity T>
__memory::managed_t<T> Next(Iterator<T>& it) {
  return it.Next();
}

template <__concepts::Entity T>
__memory::managed_t<T> Next(const __memory::handle_t<Iterator<T>>& it) {
  return Next(*it);
}

template <__concepts::Iterable T>
__memory::handle_t<Iterator<typename T::element>> Iter(T& it) {
  return it.Iter();
}

template <__concepts::Iterable T>
__memory::handle_t<Iterator<typename T::element>> Iter(
    const __memory::handle_t<T>& it) {
  return Iter(*it);
}

namespace details {

template <__concepts::Entity T>
class IteratorWrapper {
 public:
  /// @note Mamba-specific
  using element = T;
  using self = IteratorWrapper<element>;
  using iterator = __memory::handle_t<Iterator<element>>;

  using value_type = __memory::managed_t<element>;

  explicit IteratorWrapper(iterator it, bool at_end = false)
      : at_end_(at_end), it_(it) {}

  self& operator++() {
    if (at_end_) {
      return *this;
    }

    try {
      Next(it_);
    } catch (StopIteration) {
      at_end_ = true;
    }

    return *this;
  }

  self operator++(int) {
    auto res = *it_;
    this->operator++();

    return res;
  }

  value_type operator*() { return *it_; }

  bool operator==(const self& other) const {
    return at_end_ == other.at_end_ && it_ == other.it_;
  }

  bool operator!=(const self& other) const { return !(*this == other); }

  self begin() const { return *this; }
  self end() const {
    auto res = *this;
    res.at_end_ = true;
  }

 private:
  bool at_end_;
  iterator it_;
};

}  // namespace details

}  // namespace mamba::builtins
