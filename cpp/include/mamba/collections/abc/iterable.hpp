#pragma once

#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/size.hpp"

namespace mamba::builtins {
namespace details {

template <IsValid T>
class Iterator;

template <IsValid T>
class Iterable {
 public:
  using value_type = T;

  virtual ~Iterable() = default;

  virtual std::shared_ptr<Iterator<T>> Iter() const = 0;
};

template <IsValid T>
class Iterator : public Iterable<T> {
 public:
  using value_type = T;

  virtual ~Iterator() = default;

  virtual std::shared_ptr<Iterator<T>> Iter() const = 0;
};

}  // namespace details
}  // namespace mamba::builtins
