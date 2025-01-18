#pragma once

#include <concepts>
#include <iterator>
#include <memory>
#include <optional>
#include <sstream>
#include <string_view>
#include <type_traits>

#include "mamba/__utils/string_builder.hpp"
#include "mamba/builtins/__meta/subclass.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/traits.hpp"
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
  using value_type = details::Managed<T>;
  using iterator = details::IteratorFacade<details::Raw<value_type>>;

  /// @brief Mamba-specific
  using self = Iterator<value_type>;
  using next_function_t = std::function<value_type()>;

  /// @brief Constructs this iterator with a custom lambda that should be
  /// equivalent to a __Next__() invocation.
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

  virtual self __Iter__() const { return *this; }

  virtual value_type __Next__() { return data_.next_func_(); }

  static details::Str __Name__() {
    return __utils::stringify()
           << "Iterator[" << details::Traits<value_type>::kName << "]";
  }

  // Native C++ iteration support
  iterator begin() const { return iterator(*this); }
  iterator end() const { return iterator(*this, true); }

 private:
  class Data {
   public:
    bool operator==(const Data& other) const {
      return next_func_ == other.next_func_;
    }
    bool operator!=(const Data& other) const { return !(*this == other); }

    next_function_t next_func_;
  };

  Data data_;
};

namespace details {

template <typename T>
struct Traits<Iterator<T>> {
  static constexpr std::string_view kName = "Iterator";
};

template <typename T>
concept IsIterator = requires { typename T::value_type; } &&
                     SubclassOf<T, Iterator<typename T::value_type>>;

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

template <typename T>
concept Reversable = Iterable<T> && requires(T iterable) {
  { iterable.__Reversed__() } -> IteratorOf<typename T::value_type>;
};

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

template <details::Reversable T>
Iterator<typename T::value_type> Reverse(const T& it) {
  return it.__Reversed__();
}

namespace details {

/// @brief Facilitates native C++ iteration on Iterator<T>.
template <typename T>
class IteratorFacade : public std::input_iterator_tag {
 public:
  using value_type = Handle<T>;

  /// @note Mamba-specific
  using self = IteratorFacade<value_type>;
  using iterator = Iterator<Raw<value_type>>;

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
  iterator it_;
  std::optional<value_type> current_value_;
};

}  // namespace details
}  // namespace mamba::builtins
