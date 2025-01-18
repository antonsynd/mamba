#pragma once

#include <ostream>      // for ostream
#include <sstream>      // for ostream
#include <string>       // for basic_string, string
#include <string_view>  // for basic_string_view
#include <utility>      // for move

#include "mamba/builtins/__meta/optional.hpp"  // for Optional
#include "mamba/builtins/__types/bool.hpp"     // for Bool
#include "mamba/builtins/__types/byte.hpp"     // for Byte
#include "mamba/builtins/__types/decimal.hpp"  // for Decimal
#include "mamba/builtins/__types/double.hpp"   // for Double
#include "mamba/builtins/__types/float.hpp"    // for Float
#include "mamba/builtins/__types/int.hpp"      // for Int
#include "mamba/builtins/__types/long.hpp"     // for Long
#include "mamba/builtins/__types/none.hpp"     // for None
#include "mamba/builtins/__types/object.hpp"   // for Object
#include "mamba/builtins/__types/sbyte.hpp"    // for SByte
#include "mamba/builtins/__types/short.hpp"    // for Short
#include "mamba/builtins/__types/size.hpp"     // for Size
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/builtins/__types/uint.hpp"    // for UInt
#include "mamba/builtins/__types/ulong.hpp"   // for ULong
#include "mamba/builtins/__types/ushort.hpp"  // for UShort

namespace mamba::builtins::details {

// Forward-declaration
class Str;

/// @brief Convenience overload for outputting to `std::cout`/`std::cerr` or
/// `std::ostringstream`.
std::ostream& operator<<(std::ostream& oss, const Str& s);

/// @brief A class representing a Pythonic `str` type. It is bidi-convertible
/// with `std::string`. It is generally immutable unless if mutated through
/// `operator=()` and `operator+=()`.
///
/// The constructors for this class also provides the Pythonic `str()`
/// conversion function from various builtin types.
class Str final {
 public:
  Str();

  // All implicit on purpose, to be able to treat Str() as a global conversion
  // function.
  Str(const char* s);
  Str(std::string s);

  Str(const bool b);
  Str(const Bool b);
  Str(const Byte b);
  Str(const Decimal d);
  Str(const Double d);
  Str(const Float f);
  Str(const Int i);
  Str(const Long l);
  Str(const None);
  Str(const SByte s);
  Str(const Short f);
  Str(const Size s);
  Str(const UInt u);
  Str(const UShort u);
  Str(const ULong u);

  /// @brief Optional<T> returns the string representation of the payload or
  /// "None".
  template <Optional T>
  Str(const T o) {
    if (o.has_value()) {
      std::ostringstream oss;
      oss << "Optional[" << Str(o) << "]";
      data_.s_ = oss.str();
    } else {
      data_.s_ = "None";
    }
  }

  /// @brief Implicit conversion to Bool. We don't support implicit conversion
  /// to bool because it would cause equality operators between different
  /// types to fallback to bool conversion, which yields the incorrect
  /// result in many cases.
  operator Bool() const;
  explicit operator bool() const;

  Str __Repr__() const;

  Int __Len__() const;

  bool operator==(const Str& other) const;
  bool operator!=(const Str& other) const;

  /// @note For easy C++ comparison to strings.
  bool operator==(const std::string_view sv) const;
  bool operator!=(const std::string_view sv) const;

  operator std::string() const;

 private:
  class Data {
   public:
    Data() = default;
    explicit Data(std::string s) : s_(std::move(s)) {}

    bool operator==(const Data& other) const { return s_ == other.s_; }
    bool operator!=(const Data& other) const { return !(*this == other); }

    std::string s_;
  };

  mutable Data data_;
};

template <>
struct Traits<Str> {
  static constexpr std::string_view kName = "str";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
