#pragma once

#include <string_view>  // for basic_string_view, str...

#include "mamba/builtins/__types/bool.hpp"  // for Bool
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @note Forward declaration
class Str;

/// @brief Abstract base class for all objects (non-values).
class Object {
 public:
  virtual ~Object() = default;

  /// @brief Returns the representation of this object. By default, it is
  /// the evaluation of f"{__Name__()} object at {__Id__():#018x}".
  /// @code repr(object)
  virtual Str __Repr__() const;

  /// @brief Returns the string conversion of this object. By default, it is
  /// the same as __Repr__()
  /// @code str(object)
  virtual operator Str() const;

  /// @brief Returns whether this object is equivalent (but not necessarily
  /// identical) to @p other. By default, it checks the memory address of
  /// both objects.
  virtual bool operator==(const Object& other) const;
  virtual bool operator!=(const Object& other) const;

 protected:
  Str __ReprImpl__(Str name) const;

 private:
  /// @brief Emits the class name for the default implementations of __Repr__()
  /// and __Str__(). Should be overridden in subclasses.
  static Str __Name__();
};

template <>
struct Traits<Object> {
  static constexpr std::string_view kName = "object";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
