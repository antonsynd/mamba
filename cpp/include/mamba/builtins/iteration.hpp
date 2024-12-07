#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/subclass.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <typename T>
class IteratorWrapper;

}  // namespace details

/// @brief Base class for all iterators.
template <typename T>
class Iterator : public __types::Object {
 public:
  using value_type = T;
  using iterator = details::IteratorWrapper<value_type>;

  /// @brief Mamba-specific
  using self = Iterator<value_type>;

  virtual ~Iterator() = default;

  /// @brief Returns true if this and @p other are the same iterators.
  /// @code iterator == other
  virtual __types::Bool __Eq__(const self& other) const {
    return __Id__() == other.__Id__();
  }

  virtual __types::Bool __Ne__(const self& other) const {
    return !__Eq__(other);
  }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }
};

namespace __concepts {

template <typename T>
concept IsIterator = requires(const T t) {
  { T::value_type };
} && SubclassOf<T, Iterator<typename T::value_type>>;

template <typename T, typename U>
concept IteratorOf = IsIterator<T> || requires(const T iterator) {
  { iterator.__Next__() } -> std::same_as<U>;
};

template <typename T, typename U>
concept IterableOf = requires(const T iterable) {
  { iterable.__Iter__() } -> IteratorOf<U>;
};

template <typename T>
concept Iterable = IterableOf<T, typename T::value_type>;

}  // namespace __concepts

namespace details {

/// @brief Simple convenience alias.
template <__concepts::Iterable T>
using IterableValueType = typename T::value_type;

/// @brief Simple convenience alias.
template <__concepts::Iterable T>
using IterableIteratorType = Iterator<IterableValueType<T>>;

}  // namespace details

template <typename T, typename U>
  requires __concepts::IteratorOf<T, U>
U Next(T& it) {
  return it.__Next__();
}

template <__concepts::Iterable T>
details::IterableIteratorType<T> Iter(const T& it) {
  return it.__Iter__();
}

namespace details {

/// @brief Facilitates native C++ iteration.
template <typename T>
class IteratorWrapper {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = IteratorWrapper<value_type>;
  using iterator = Iterator<value_type>;

  /// @brief Constructs a C++ wrapper for a Mamba iterator. The internal state
  /// of @p it is shared with the original by virtue of being a shallow copy.
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
  // C++ only facility, no need to create std::shared_ptr<Data> over these
  // members.
  bool at_end_;
  iterator it_;
};

}  // namespace details
}  // namespace mamba::builtins
