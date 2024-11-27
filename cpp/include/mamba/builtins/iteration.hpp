#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__memory/mut.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <typename T>
class IteratorWrapper;

}  // namespace details

template <typename T>
class Iterator : public builtins::__types::Object {
 public:
  using value_type = T;
  using iterator = details::IteratorWrapper<value_type>;

  /// @brief Mamba-specific
  using self = Iterator<value_type>;

  virtual ~Iterator() = default;

  virtual __memory::Mut<Iterator<value_type>> __Iter__() = 0;

  /// @brief Returns the next value from the iterator, starting from the first
  /// value.
  /// @code next(iterator)
  virtual value_type __Next__() = 0;

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code list == other
  __types::Bool __Eq__(const self& other) const { return this == &other; }
  __types::Bool __Ne__(const self& other) const { return !__Eq__(other); }

  bool operator!=(const self& other) const { return !__Ne__(other); }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }
};

namespace __concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->__Iter__() } -> std::same_as<__memory::Mut<Iterator<U>>>;
};

template <typename T>
concept Iterable = TypedIterable<T, typename T::element>;

}  // namespace __concepts

template <typename T>
T Next(Iterator<T>& it) {
  return it.__Next__();
}

template <typename T>
T Next(__memory::Const<Iterator<T>> it) {
  return Next(*it);
}

template <__concepts::Iterable T>
__memory::Mut<Iterator<T>> Iter(T& it) {
  return it.__Iter__();
}

template <__concepts::Iterable T>
__memory::Mut<Iterator<T>> Iter(__memory::Const<T> it) {
  return Iter(*it);
}

namespace details {

template <typename T>
class IteratorWrapper {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = IteratorWrapper<value_type>;
  using iterator = __memory::Mut<Iterator<value_type>>;

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
