#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

#include "mamba/__concepts/comparable.hpp"
#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/as_str.hpp"
#include "mamba/builtins/comparators.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba::builtins {

namespace details {

// Concept to check if all types are the same
template <typename T, typename... Args>
concept Homogenous = (std::same_as<T, Args> && ...);

// Concept to check if types are different (not all the same)
template <typename... Args>
concept Heterogeneous = !Homogenous<Args...>;

}  // namespace details

template <typename... Args>
  requires details::Heterogeneous<Args...>
class Tuple {
 public:
  __types::Bool In(elem) const;
  __types::Int Len() const;

 private:
};

// Could be base class of List<T>
template <typename T, typename... Args>
  requires details::Homogenous<T, Args...>
class Tuple {
 public:
  using element = T;

  using value = __memory::managed_t<element>;

  __types::Bool In(__memory::ReadOnly<element> elem) const;
  __types::Int Len() const;

  // Only enabled if tuple is of one type
  /// @brief Returns an iterator to this list.
  /// @code list.__iter__()
  __memory::handle_t<Iterator<element>> Iter() {
    return details::TupleIterator<element>::Init(v_.begin(), v_.end());
  }

  // Only enable if the tuple is of one type
  // __memory::managed_t<U> Max() const;
  // __memory::managed_t<U> Min() const;

 private:
};

namespace details {

template <__concepts::Entity T>
class TupleIterator : public Iterator<T>,
                      public std::enable_shared_from_this<TupleIterator<T>> {
 public:
  using element = T;

  using value = __memory::managed_t<element>;

  using iterator = Tuple<element>::iterator;
  using const_iterator = Tuple<element>::const_iterator;

  using self = TupleIterator<element>;
  using handle = __memory::handle_t<self>;

  TupleIterator(iterator it, iterator end)
      : it_(std::move(it)), end_(std::move(end)) {}

  ~TupleIterator() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code TupleIterator.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  __memory::handle_t<Iterator<element>> Iter() override {
    return std::enable_shared_from_this<self>::shared_from_this();
  }

  value Next() override {
    if (it_ == end_) {
      throw StopIteration("end of iterator");
    }

    return *it_++;
  }

  __types::Str Repr() const override { return "TupleIterator"; }

  // Native support for C++ for..each loops
  iterator begin() { return it_; }
  iterator end() { return end_; }
  const_iterator begin() const { return it_; }
  const_iterator end() const { return end_; }
  const_iterator cbegin() const { return it_; }
  const_iterator cend() const { return end_; }

 private:
  iterator it_;
  iterator end_;
};

}  // namespace details

}  // namespace mamba::builtins
