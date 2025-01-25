#pragma once

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Container {
 public:
  using value_type = T;

  virtual bool Contains(const value_type& elem) const = 0;
};

}  // namespace mamba::collections::abc
