#pragma once

#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/size.hpp"
#include "mamba/builtins/iteration.hpp"

namespace mamba::builtins {
namespace details {

template <IsValid T>
class Sequence : public Iterable<T> {
 public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;

  virtual ~Sequence() = default;

  virtual bool Contains(const_reference elem) const = 0;
  virtual Size Len() const = 0;
  virtual value_type Max() const = 0;
  virtual value_type Min() const = 0;
};

}  // namespace details
}  // namespace mamba::builtins
