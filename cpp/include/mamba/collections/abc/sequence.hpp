#pragma once

#include <utility>

#include "mamba/builtins/__meta/type_validity.hpp"
#include "mamba/builtins/__types/size.hpp"
#include "mamba/builtins/__types/ssize.hpp"
#include "mamba/collections/abc/iteration.hpp"
#include "mamba/collections/abc/reversible.hpp"

namespace mamba::collections::abc {

template <builtins::details::IsValid T>
class Sequence : virtual public Collection<T>, virtual public Reversible<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = Sequence<T>;

  virtual builtins::details::Size Count(const value_type& elem) const = 0;

  virtual builtins::details::Size Index(
      const value_type& elem,
      const builtins::details::Size start = 0) const = 0;
  virtual builtins::details::Size Index(
      const value_type& elem,
      const builtins::details::Size start,
      const builtins::details::Size end) const = 0;

  virtual const value_type& operator[](const builtins::details::Size) const = 0;

  virtual std::shared_ptr<self> Slice(
      builtins::details::SSize start = 0,
      builtins::details::SSize end = builtins::details::kSSizeMax,
      builtins::details::SSize step = 1) const = 0;

#if __cplusplus >= 202302L
  virtual std::shared_ptr<self> operator[](
      builtins::details::SSize start = 0,
      builtins::details::SSize end = builtins::details::kSSizeMax,
      builtins::details::SSize step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L
};

}  // namespace mamba::collections::abc
