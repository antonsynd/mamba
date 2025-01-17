#include "mamba/builtins/__types/bool.hpp"

#include "mamba/builtins/__types/double.hpp"  // for Double
#include "mamba/builtins/__types/float.hpp"   // for Float
#include "mamba/builtins/__types/int.hpp"     // for Int
#include "mamba/builtins/__types/none.hpp"    // for None

namespace mamba::builtins::details {

Bool::Bool() = default;

Bool::Bool(const bool b) : b_(b) {}

Bool::Bool(const Byte b) : b_(b) {}

Bool::Bool(const Decimal d) : b_(d) {}

Bool::Bool(const Double d) : b_(d) {}

Bool::Bool(const Int i) : b_(i) {}

Bool::Bool(const Float f) : b_(f) {}

Bool::Bool(const Long l) : b_(l) {}

Bool::Bool(const None) {}

Bool::Bool(const SByte s) : b_(s) {}

Bool::Bool(const Short s) : b_(s) {}

Bool::Bool(const Size s) : b_(s) {}

Bool::Bool(const UInt u) : b_(u) {}

Bool::Bool(const ULong u) : b_(u) {}

Bool::Bool(const UShort u) : b_(u) {}

bool Bool::operator==(const Bool& other) const {
  return b_ == other.b_;
}

bool Bool::operator!=(const Bool& other) const {
  return !(*this == other);
}

Bool::operator bool() const {
  return b_;
}

Bool::operator Byte() const {
  return 0;
}

Bool::operator Decimal() const {
  return 0;
}

Bool::operator Double() const {
  return 0;
}

Bool::operator Float() const {
  return 0;
}

Bool::operator Int() const {
  return 0;
}

Bool::operator Long() const {
  return 0;
}

Bool::operator SByte() const {
  return 0;
}

Bool::operator Short() const {
  return 0;
}

Bool::operator Size() const {
  return 0;
}

Bool::operator UInt() const {
  return 0;
}

Bool::operator ULong() const {
  return 0;
}

Bool::operator UShort() const {
  return 0;
}

}  // namespace mamba::builtins::details
