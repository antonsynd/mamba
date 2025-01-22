#pragma once

#include "mamba/builtins/__meta/type_validity.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Container {
  using value_type = T;

  virtual bool Contains(const value_type& elem) = 0;
};

}  // namespace mamba::collections::abc
