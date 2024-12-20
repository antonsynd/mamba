#pragma once

#include <string_view>  // for basic_string_view, str...

#include "mamba/builtins/__types/big_int.hpp"  // for BigInt
#include "mamba/builtins/__types/bool.hpp"     // for Bool
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @note Forward declaration
class Str;

/// @brief Abstract base class for all objects (non-values).
class Object {
 public:
  /// @note Mamba-specific alias for brevity.
  using self = Object;

  virtual ~Object() = default;

  /// @brief Emits the class name for the default implementations of __Repr__()
  /// and __Str__(). Should be overridden in subclasses.
  virtual Str __Name__() const;

  /// @brief Returns the representation of this object. By default, it is
  /// the evaluation of f"{__Name__()} object at {__Id__():#018x}".
  /// @code repr(object)
  virtual Str __Repr__() const;

  /// @brief Returns the string conversion of this object. By default, it is
  /// the same as __Repr__()
  /// @code str(object)
  virtual Str __Str__() const;

  /// @brief Returns the bool conversion of this object. By default, it always
  /// returns True.
  /// @code bool(object)
  virtual Bool __Bool__() const;

  /// @brief Returns whether this object is equivalent (but not necessarily
  /// identical) to @p other. By default, it compares the __Id__() of both
  /// objects. Thus, for different subclasses of objects, this should always
  /// evaluate to false unless a more specific overload is specified.
  virtual Bool __Eq__(const self& other) const;

  /// @brief Returns the unique id of this object. Must be overridden by
  /// subclasses. Typically, it returns the memory address of the object's
  /// internal data.
  virtual BigInt __Id__() const = 0;

  /// @note For C++ conversion to bool. It needs to be explicit to avoid the
  /// C++ compiler from choosing to convert to bool when doing equality checks
  /// with the global operator==().
  virtual explicit operator bool() const;

  /// @note Mainly for C++ code generation. It is equivalent to __Eq__().
  virtual bool operator==(const self& other) const;
  virtual bool operator!=(const self& other) const;

  /// @note For C++ code generation, facilitating the implementation of the
  /// identity operator like so: ~a == ~b. Underlyingly, this calls __Id__().
  virtual BigInt operator~() const;
};

template <>
struct Traits<Object> {
  static constexpr std::string_view kName = "object";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
