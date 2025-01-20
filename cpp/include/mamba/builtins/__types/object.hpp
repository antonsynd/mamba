#pragma once

#include <memory>
#include <string_view>  // for basic_string_view, str...

#include "mamba/builtins/__types/bool.hpp"  // for Bool
#include "mamba/builtins/__types/forward_declarations.hpp"
#include "mamba/builtins/__types/size.hpp"  // for Size
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief Abstract base class for all objects (non-value types).
class Object : public std::enable_shared_from_this<Object> {
 public:
  /// @note Needed to ensure proper destruction of any derived objects.
  virtual ~Object() = default;

  /// @brief Returns the id of this object, which is its memory address.
  /// @code id(object)
  virtual Size Id() const final;

  /// @brief Returns the representation of this object. By default, it is
  /// the evaluation of f"{_Repr(...) object at {Id():#018x}".
  /// @code repr(object)
  virtual Str Repr() const;

  /// @brief Returns the string conversion of this object. By default, it is
  /// the same as @ref Repr().
  /// @code str(object)
  virtual operator Str() const;

  /// @brief Returns whether this object is equivalent (but not necessarily
  /// identical) to @p other. By default, it checks the memory address of
  /// both objects.
  virtual bool operator==(const Object& other) const;
  virtual bool operator!=(const Object& other) const;

 protected:
  /// @brief Returns an `std::shared_ptr` to this object.
  virtual std::shared_ptr<Object> _GetRef() final;

  /// @brief Invoked by @ref Repr() to inject the object's current name into
  /// the default output of @ref Repr().
  virtual Str _Repr(const std::string_view name) const;
};

template <>
struct Traits<Object> {
  static constexpr std::string_view kName = "object";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
