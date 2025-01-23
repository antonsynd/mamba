#pragma once

#include <memory>
#include <optional>
#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/error.hpp"

namespace mamba::collections::abc {

// Forward-declaration
template <builtins::details::IsValid T>
class Iterator;

template <builtins::details::IsValid T>
class Iterable : virtual public builtins::details::Object {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using iterator_type = Iterator<value_type>;

  virtual ~Iterable() = default;

  virtual std::shared_ptr<iterator_type> Iter() const = 0;
};

template <builtins::details::IsValid T>
class Iterator : virtual public Iterable<T> {
 public:
  using value_type = T;
  using iterator = details::IteratorFacade<value_type>;

  /// @note Mamba-specific
  using next_function_t = std::function<value_type()>;
  using self = Iterator<value_type>;

  /// @brief Constructs this iterator with a custom lambda that should be
  /// equivalent to a Next() invocation.
  explicit Iterator(next_function_t next_func) : data_(std::move(next_func)) {}

  /// @brief Constructs this iterator over standard C++ forward iterators
  /// which must be have a lifetime at least as long as this iterator, which
  /// is enforced by the std::shared_ptr parameters.
  ///
  /// @note Internally, this constructs capturing lambdas to invoke the
  /// relevant iterator methods (dereference and sentinel detection).
  template <std::forward_iterator It>
  Iterator(It begin, It end)
      : data_([it = std::move(begin),
               end = std::move(end)]() mutable -> value_type {
          if (it == end) {
            throw StopIteration();
          }

          auto res = *it;
          ++it;

          return res;
        }) {}

  virtual ~Iterator() = default;

  virtual value_type Next() { return data_.next_func_(); }
  virtual std::shared_ptr<self> Iter() const {
    return std::make_shared<self>(*this);
  }

  /// @brief Iterators are only equal if they are the same object.
  bool operator==(const self& other) const { return this == &other; }
  bool operator!=(const self& other) const { return !(*this == other); }

  // For generic comparison with other object types.
  using builtins::details::Object::operator==();
  using builtins::details::Object::operator!=();

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }

 private:
  class Data {
    next_function_t next_func_;
  };

  Data data_;
};

namespace details {

/// @brief Facilitates native C++ iteration on Iterator<T>.
template <builtins::details::IsValid T>
class IteratorFacade : public std::input_iterator_tag {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = IteratorFacade<value_type>;
  using iterator_type = Iterator<value_type>;

  /// @brief Constructs a C++ wrapper for a Mamba iterator. The internal state
  /// of @p it is shared with the original by virtue of being a shallow copy.
  explicit IteratorFacade(iterator it, bool at_end = false)
      : it_(it), current_value_(std::nullopt) {
    if (!at_end) {
      UncheckedAdvance();
    }
  }

  /// @note Only pre-increment is supported. Post-increment requires
  /// deep-copying of the underlying which is not trivial.
  self& operator++() {
    Advance();
    return *this;
  }

  self operator++(int) {
    auto res = *this;
    ++(*this);

    return res;
  }

  value_type operator*() {
    if (!current_value_) {
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
  iterator_type it_;
  std::optional<value_type> current_value_;
};
}  // namespace details

}  // namespace mamba::collections::abc
