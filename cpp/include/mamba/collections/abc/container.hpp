#pragma once

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Container : virtual public builtins::details::Object {
  using value_type = T;

  virtual bool Contains(const value_type& elem) = 0;
};

}  // namespace mamba::collections::abc
