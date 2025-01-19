#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"

namespace mamba::builtins::details {

/// @brief A shared pointer implementation for Mamba objects that offers
/// bidi-conversion with `std::shared_ptr<T>`. This implementation is needed
/// to provide implicit conversion to the underlying type for generic
/// programming.
template <IsNotValue T>
class Ref {
 public:
  using element_type = T;
  using shared_type = std::shared_ptr<element_type>;

  /// @brief Implicitly convertible from `std::shared_ptr<T>`.
  Ref(shared_type&& ptr) : ptr_(std::forward<shared_type>(ptr)) {}

  /// @brief Moves @p obj into a new `std::shared_ptr<T>`.
  explicit Ref(T&& obj) : ptr_(std::move(obj)) {}

  /// @brief Implicitly convertible to `std::shared_ptr<T>`.
  operator shared_type() const { return ptr_; }

  /// @brief Implicitly convertible to `T&`. This may result in undefined
  /// behavior if this is the only remaining reference to the object and it is
  /// passed into a function that
  operator element_type&() const { return *ptr_; }
  operator element_type() && const { return std::move(*ptr_); }

  /// @brief Dereferences to `T&`.
  element_type& operator*() const { return *ptr_; }
  element_type* operator->() const { return ptr_.get(); }

  Ref Clone() const { return *this; }
  shared_type Ptr() const { return ptr_; }

 private:
  mutable shared_type ptr_;
};

}  // namespace mamba::builtins::details
