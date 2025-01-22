#pragma once

#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/collections/abc/sequence.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Sequence : virtual public Sequence<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = Sequence<value_type>;

  virtual void Append(value_type&& elem) = 0;
  virtual void Clear() = 0;
  virtual void Reverse() = 0;
  virtual void Extend() = 0;
  virtual void Insert(value_type&& elem) = 0;
  virtual void Pop() = 0;
  virtual void Remove() = 0;

  virtual self& operator+=() = 0;
};

}  // namespace mamba::collections::abc
