#pragma once

#include <memory>
#include <string_view>  // for basic_string_view, str...

#include "mamba/builtins/__types/bool.hpp"  // for Bool
#include "mamba/builtins/__types/forward_declarations.hpp"
#include "mamba/builtins/__types/size.hpp"  // for Size
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief Abstract base class for all objects (non-values).
class Object : public std::enable_shared_from_this<Object> {
 public:
  virtual ~Object() = default;

  /// @brief Returns the id of this object, which is its memory address.
  virtual Size Id() const final;

  /// @brief Returns the representation of this object. By default, it is
  /// the evaluation of f"{Name()} object at {Id():#018x}".
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
  std::shared_ptr<Object> _GetRef();

  Str _Repr(std::string name) const;
};

template <>
struct Traits<Object> {
  static constexpr std::string_view kName = "object";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
