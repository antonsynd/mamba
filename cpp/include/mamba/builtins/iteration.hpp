#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <typename T>
class IteratorWrapper;

}  // namespace details

template <typename T>
class Iterator : public __types::Object {
 public:
  using value_type = T;
  using iterator = details::IteratorWrapper<value_type>;

  /// @brief Mamba-specific
  using self = Iterator<value_type>;
  using shared = std::shared_ptr<self>;

  virtual ~Iterator() = default;

  virtual shared __Iter__() = 0;

  /// @brief Returns the next value from the iterator, starting from the first
  /// value.
  /// @code next(iterator)
  virtual value_type __Next__() = 0;

  /// @brief Returns true if this and @p other are the same iterators.
  /// @code iterator == other
  virtual __types::Bool __Eq__(const shared& other) const {
    return this == other.get();
  }

  virtual __types::Bool __Ne__(const shared& other) const {
    return !__Eq__(other);
  }

  bool operator==(const shared& other) const { return !__Eq__(other); }
  bool operator!=(const shared& other) const { return !__Ne__(other); }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }
};

namespace __concepts {

template <typename T, typename U>
concept IterableOf = requires(T iterable) {
  { iterable->__Iter__() } -> std::same_as<std::shared_ptr<Iterator<U>>>;
};

template <typename T>
concept Iterable = IterableOf<T, typename T::element_type::value_type>;

}  // namespace __concepts

namespace details {

template <__concepts::Iterable T>
using IterableValueType = typename T::element_type::value_type;

template <__concepts::Iterable T>
using IterableIteratorType = Iterator<IterableValueType<T>>;

}  // namespace details

template <__concepts::Iterable T>
details::IterableValueType<T> Next(const T& it) {
  return it->__Next__();
}

template <__concepts::Iterable T>
std::shared_ptr<details::IterableIteratorType<T>> Iter(const T& it) {
  return it->__Iter__();
}

namespace details {

template <typename T>
class IteratorWrapper {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = IteratorWrapper<value_type>;
  using shared = std::shared_ptr<self>;
  using iterator = std::shared_ptr<Iterator<value_type>>;

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

  bool operator==(const shared& other) const {
    return at_end_ == other->at_end_ && it_ == other->it_;
  }

  bool operator!=(const shared& other) const { return !(*this == other); }

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
