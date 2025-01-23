#pragma once

#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/size.hpp"
#include "mamba/builtins/__types/ssize.hpp"
#include "mamba/collections/abc/sequence.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class MutableSequence : virtual public Sequence<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = MutableSequence<value_type>;

  virtual void Append(value_type&& elem) = 0;

  virtual void Clear() = 0;

  virtual void Extend(const Sequence<T>& other) = 0;

  virtual void Insert(const builtins::details::Size idx, value_type&& elem) = 0;

  virtual value_type Pop(const builtins::details::SSize idx = -1) = 0;

  virtual void Reverse() = 0;

  virtual void Remove(const value_type& elem) = 0;

  virtual self& operator+=(const self& other) = 0;

  virtual value_type& operator[](const builtins::details::Size) = 0;

  /// @brief Deletes the elements in the given slice. See Slice() for the
  /// behavior of the parameters.
  /// @code del list[i:j(:k)]
  virtual void DeleteSlice(
      builtins::details::Size start = 0,
      builtins::details::Size end = builtins::details::kSSizeMax,
      builtins::details::Size step = 1) = 0;

  /// @brief Replaces the given slice with the elements of @p other. If @p step
  /// is not 1, then the length of @p other must be equal to the length of the
  /// slice, otherwise a ValueError will be thrown.
  /// @code list[i:j:k] = other
  virtual void ReplaceSlice(
      const self& other,
      builtins::details::Size start = 0,
      builtins::details::Size end = builtins::details::kSSizeMax,
      builtins::details::Size step = 1) = 0;
};

}  // namespace mamba::collections::abc
