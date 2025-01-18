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

/// @brief Constructs a `str` via a literal.
Str operator""_str(const char* s, std::size_t len);

/// @brief A class representing a Pythonic `str` type. It is bidi-convertible
/// with `std::string`. It is generally immutable unless if mutated through
/// `operator=()` and `operator+=()`. In general, any Mamba API that deals with
/// strings should work with C++ `std::string` or `std::string_view` where
/// possible and only use this `str` class when Pythonic APIs are required.
///
/// The constructors for this class provide the Pythonic `str()` conversion
/// function from various builtin types, mainly other numeric value types.
class Str final {
 public:
  /// @brief Constructs an empty `str`.
  Str();

  /// @overload
  /// @brief Constructs a `str` from various other types, including C++ string
  /// representations. These are all implicit to also serve as the Pythonic
  /// `str()` conversion function.
  Str(const char* s);
  Str(const char* s, std::size_t len);
  Str(std::string s);
  Str(const std::string_view s);
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

  /// @overload
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

  /// @todo
  Str Capitalize() const { return *this; }
  Str Casefold() const { return *this; }
  Str Center(const Size width, const std::string fillchar = " ") const {
    return *this;
  }
  Size Count(const std::string_view sub,
             const Size start = 0,
             const Size end = kSizeMax) {
    return 0;
  }
  /// @todo Change return type to immutable bytes.
  Str Encode(const std::string_view encoding = "utf-8",
             const std::string_view errors = "strict") const {
    return *this;
  }
  bool EndsWith(const std::string_view suffix,
                const Size start = 0,
                const Size end = kSizeMax) const {
    return false;
  }
  Str ExpandTabs(Size tabsize = 8) const { return *this; }
  /// @todo Figure out how to encode -1 as a return value for no results.
  Size Find(const std::string_view sub,
            const Size start = 0,
            const Size end = kSizeMax) const {
    return 0;
  }

  /// @todo
  template <typename... Args>
  Str Format() const {
    return *this;
  }

  /// @todo
  Str FormatMap() { return *this; }
  Size Index(const std::string_view sub,
             const Size start = 0,
             const Size end = kSizeMax) const {
    return 0;
  }
  bool IsAlnum() const { return false; }
  bool IsAlpha() const { return false; }
  bool IsAscii() const { return false; }
  bool IsDecimal() const { return false; }
  bool IsDigit() const { return false; }
  bool IsIdentifier() const { return false; }
  bool IsLower() const { return false; }
  bool IsNumeric() const { return false; }
  bool IsPrintable() const { return false; }
  bool IsSpace() const { return false; }
  bool IsTitle() const { return false; }
  bool IsUpper() const { return false; }
  Str Join(void* iterable) const {}
  Str LJust(const Size width, const std::string_view fillchar = " ") const {
    return *this;
  }
  Str Lower() const { return *this; }
  Str LStrip(void* chars) const { return *this; }
  Str Partition(void* sep) const { return *this; }
  Str RemovePrefix(const std::string_view prefix) const { return *this; }
  Str RemoveSuffix(const std::string_view suffix) const {}
  Str Replace(const std::string_view oldstr,
              const std::string_view newstr,
              Size count = kSizeMax) const {}
  Str RFind(const std::string_view sub,
            Size start = 0,
            Size end = kSizeMax) const {
    return *this;
  }
  Str RIndex(const std::string_view sub,
             Size start = 0,
             Size end = kSizeMax) const {
    return *this;
  }
  Str RJust(Size width, const std::string_view fillchar = " ") const {
    return *this;
  }
  Str RPartition(void* sep) const { return *this; }
  Str RSplit(void* sep = nullptr, const Size maxsplit = kSizeMax) const {
    return *this;
  }
  Str RStrip(void* chars) const { return *this; }
  Str Split(const std::string_view sep = "",
            const Size maxsplit = kSizeMax) const {
    return *this;
  }
  Str SplitLines(const bool keepends = false) const { return *this; }
  Str StartsWith(const std::string_view prefix,
                 const Size start = 0,
                 const Size end = kSizeMax) const {
    return *this;
  }
  Str Strip(void* chars) const { return *this; }
  Str SwapCase() const { return *this; }
  Str Title() const { return *this; }
  Str Translate(void* table) const { return *this; }
  Str Upper() const { return *this; }

  /// @brief Implicit conversion to @ref Bool, treating an empty `str` as
  /// `false` and non-empty `str` as `true`.
  operator Bool() const;

  /// @brief Explicit conversion to `bool` using the same semantics as
  /// @ref operator Bool().
  /// @note Implicit conversion is blocked because it would cause
  /// `operator==()` between different types to convert to `bool`, which yields
  /// the incorrect result in many cases where a better suited overload
  /// should've been invoked.
  explicit operator bool() const;

  /// @brief Returns a copy of the `str` itself.
  Str __Repr__() const;

  /// @brief Returns the length of the `str` in terms of Unicode codepoints.
  /// @todo Actually return codepoint count, not the byte count.
  Int __Len__() const;

  /// @overload
  /// @brief Compares this `str` with @p other. They are equal if they have
  /// the same byte content.
  bool operator==(const Str& other) const;
  bool operator!=(const Str& other) const;

  /// @overload
  /// @brief Compares this `str` with C++ `std::string_view` objects. Mostly
  /// for convenience in code generation with string literals.
  bool operator==(const std::string_view sv) const;
  bool operator!=(const std::string_view sv) const;

  /// @overload
  /// @brief Implicit conversion to `std::string` or `std::string_view`.
  operator std::string() const;
  operator std::string_view() const;

 private:
  class Data {
   public:
    Data() = default;
    explicit Data(const char* s) : s_(s) {}
    Data(const char* s, std::size_t len) : s_(s, len) {}
    explicit Data(std::string s) : s_(std::move(s)) {}
    explicit Data(const std::string_view s) : s_(s) {}

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
