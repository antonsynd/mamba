#include "mamba/builtins/__types/str.hpp"

#include <iostream>
#include <string>       // for basic_string, to_string
#include <string_view>  // for basic_string_view, ope...

#include "mamba/builtins/__types/byte.hpp"     // for Byte
#include "mamba/builtins/__types/decimal.hpp"  // for Decimal
#include "mamba/builtins/__types/double.hpp"   // for Double
#include "mamba/builtins/__types/float.hpp"    // for Float
#include "mamba/builtins/__types/int.hpp"      // for Int
#include "mamba/builtins/__types/long.hpp"     // for Long
#include "mamba/builtins/__types/sbyte.hpp"    // for SByte
#include "mamba/builtins/__types/short.hpp"    // for Short
#include "mamba/builtins/__types/size.hpp"     // for Size
#include "mamba/builtins/__types/uint.hpp"     // for UInt
#include "mamba/builtins/__types/ulong.hpp"    // for ULong
#include "mamba/builtins/__types/ushort.hpp"   // for UShort

namespace mamba::builtins::details {

Str::Str() = default;

Str::Str(const char* s) : data_(s) {}

Str::Str(std::string s) : data_(std::move(s)) {}

Str::Str(const bool b) : data_(b ? "True" : "False") {}

Str::Str(const Bool b) : data_(b ? "True" : "False") {}

Str::Str(const Byte b) : data_(std::to_string(b)) {}

Str::Str(const Decimal d) : data_(std::to_string(d)) {}

Str::Str(const Double d) : data_(std::to_string(d)) {}

Str::Str(const Float f) : data_(std::to_string(f)) {}

Str::Str(const Int i) : data_(std::to_string(i)) {}

Str::Str(const None) : data_("None") {}

Str::Str(const Long l) : data_(std::to_string(l)) {}

Str::Str(const SByte s) : data_(std::to_string(s)) {}

Str::Str(const Short s) : data_(std::to_string(s)) {}

Str::Str(const Size s) : data_(std::to_string(s)) {}

Str::Str(const UInt u) : data_(std::to_string(u)) {}

Str::Str(const ULong u) : data_(std::to_string(u)) {}

Str::Str(const UShort u) : data_(std::to_string(u)) {}

Str::operator std::string() const {
  return data_.s_;
}

Str Str::__Name__() {
  return "string";
}

Str::operator Bool() const {
  return !data_.s_.empty();
}

Str Str::__Repr__() const {
  // A copy
  return *this;
}

Int Str::__Len__() const {
  return data_.s_.size();
}

bool Str::operator==(const Str& other) const {
  return data_ == other.data_;
}

bool Str::operator!=(const Str& other) const {
  return !(*this == other);
}

/// @note For easy C++ comparison to strings.
bool Str::operator==(const std::string_view sv) const {
  return data_.s_ == sv;
}
bool Str::operator!=(const std::string_view sv) const {
  return !(*this == sv);
}

std::ostream& operator<<(std::ostream& oss, const Str& s) {
  oss << static_cast<std::string>(s);
  return oss;
}

}  // namespace mamba::builtins::details
