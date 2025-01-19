#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

template <typename T>
struct Arg {
 public:
  using element_type = std::conditional_t<IsWrapped<T>, Unwrapped<T>, T>;

  Arg(element_type& t) : t_(&t), shared_(nullptr) {}

  Arg(std::shared_ptr<element_type> t) : t_(t.get()), shared_(std::move(t)) {}

  Arg(element_type&& t)
      : t_(nullptr), shared_(std::make_shared<T>(std::move(t))) {
    t_ = shared_.get();
  }

  /// @brief Implicit conversion to `element_type`.
  operator element_type&() const { return *t_; }

  /// @brief Dereferences to `element_type&`.
  element_type& operator*() const { return *t_; }

  /// @brief Indirection to the underlying `element_type*` pointer.
  element_type* operator->() const { return t_; }

 private:
  mutable element_type* t_;
  mutable std::shared_ptr<element_type>& shared_;
};

}  // namespace mamba::builtins::details
