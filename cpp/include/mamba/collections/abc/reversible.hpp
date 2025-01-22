#pragma once

#include <memory>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/collections/abc/iteration.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Reversible : virtual public Iterable<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using iterable_type = Iterable<value_type>;

  virtual std::shared_ptr<iterable_type> Reversed() const = 0;
};

}  // namespace mamba::collections::abc
