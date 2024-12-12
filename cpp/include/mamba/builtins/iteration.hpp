#pragma once

#include <concepts>
#include <iterator>
#include <memory>
#include <optional>
#include <type_traits>

#include "mamba/builtins/__concepts/subclass.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <typename T>
class IteratorFacade;

}  // namespace details

/// @brief Base class for all iterators.
template <typename T>
class Iterator : public details::Object {
 public:
  using value_type = T;
  using iterator = details::IteratorFacade<value_type>;

  /// @brief Mamba-specific
  using self = Iterator<value_type>;
  using next_function_t = std::function<value_type()>;

  /// @brief Constructs this iterator with a custom lambda that should be
  /// equivalent to a __Next__() invocation.
  explicit Iterator(next_function_t next_func)
      : data_(std::make_shared<Data>(std::move(next_func))) {}

  /// @brief Constructs this iterator over standard C++ forward iterators
  /// which must be have a lifetime at least as long as this iterator, which
  /// is enforced by the std::shared_ptr parameters.
  ///
  /// @note Internally, this constructs capturing lambdas to invoke the
  /// relevant iterator methods (dereference and sentinel detection).
  template <std::forward_iterator It>
  Iterator(It begin, It end)
      : data_(std::make_shared<Data>(
            [it = std::move(begin),
             end = std::move(end)]() mutable -> value_type {
              if (it == end) {
                throw StopIteration();
              }

              auto res = *it;
              ++it;

              return res;
            })) {}

  virtual ~Iterator() = default;

  virtual details::Str __Repr__() const override { return "Iterator"; }

  virtual self __Iter__() const { return *this; }

  virtual value_type __Next__() { return data_->next_func_(); }

  virtual details::BigInt __Id__() const override {
    return reinterpret_cast<details::BigInt>(data_.get());
  }

  constexpr details::Bool __Bool__() const override { return true; }

  /// @brief Returns true if this and @p other are the same iterators.
  /// @code iterator == other
  virtual details::Bool __Eq__(const self& other) const {
    return __Id__() == other.__Id__();
  }

  virtual details::Bool __Ne__(const self& other) const {
    return !__Eq__(other);
  }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }

 private:
  class Data {
   public:
    next_function_t next_func_;
  };

  std::shared_ptr<Data> data_;
};

namespace details {

template <typename T>
concept IsIterator = requires(const T t) {
  { T::value_type };
} && SubclassOf<T, Iterator<typename T::value_type>>;

template <typename T, typename U>
concept IteratorOf = IsIterator<T> || requires(T iterator) {
  { iterator.__Next__() } -> std::same_as<U>;
};

template <typename T, typename U>
concept IterableOf = requires(const T iterable) {
  { iterable.__Iter__() } -> IteratorOf<U>;
};

template <typename T>
concept Iterable = IterableOf<T, typename T::value_type>;

/// @brief Simple convenience alias.
template <Iterable T>
using IterableValueType = typename T::value_type;

/// @brief Simple convenience alias.
template <Iterable T>
using IterableIteratorType = Iterator<IterableValueType<T>>;

}  // namespace details

template <details::IsIterator T>
typename T::value_type Next(T& it) {
  return it.__Next__();
}

template <details::Iterable T>
Iterator<typename T::value_type> Iter(const T& it) {
  return it.__Iter__();
}

namespace details {

/// @brief Facilitates native C++ iteration on Iterator<T>.
template <typename T>
class IteratorFacade : public std::input_iterator_tag {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = IteratorFacade<value_type>;
  using iterator = Iterator<value_type>;

  /// @brief Constructs a C++ wrapper for a Mamba iterator. The internal state
  /// of @p it is shared with the original by virtue of being a shallow copy.
  explicit IteratorFacade(iterator it, bool at_end = false)
      : it_(it), current_value_(std::nullopt) {
    UncheckedAdvance();
  }

  /// @note Only pre-increment is supported. Post-increment requires
  /// deep-copying of the underlying which is not trivial.
  self& operator++() {
    Advance();
    return *this;
  }

  value_type operator*() {
    if (current_value_) {
      throw ValueError(
          "Mamba-internal error: Cannot dereference an iterator that has "
          "already thrown StopIterator.");
    }

    return *current_value_;
  }

  bool operator==(const self& other) const {
    return !!current_value_ == !!other.current_value_ && it_ == other.it_;
  }

  bool operator!=(const self& other) const { return !(*this == other); }

  self begin() const { return *this; }

  self end() const {
    auto res = *this;
    res.current_value_.reset();

    return res;
  }

 private:
  void UncheckedAdvance() {
    try {
      current_value_ = it_.__Next__();
    } catch (StopIteration) {
      current_value_.reset();
    }
  }

  void Advance() {
    if (!current_value_) {
      // No-op
      return;
    }

    UncheckedAdvance();
  }

  // C++ only facility, no need to create std::shared_ptr<Data> over these
  // members.
  iterator it_;
  std::optional<value_type> current_value_;
};

}  // namespace details
}  // namespace mamba::builtins
