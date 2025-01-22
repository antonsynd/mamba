#pragma once

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/collections/abc/container.hpp"
#include "mamba/collections/abc/iteration.hpp"
#include "mamba/collections/abc/sized.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Collection : virtual public Sized,
                   virtual public Iterable<T>,
                   virtual public Container<T> {};

}  // namespace mamba::collections::abc
