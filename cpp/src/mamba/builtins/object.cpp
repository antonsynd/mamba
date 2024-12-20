#include "mamba/builtins/__types/object.hpp"

#include <memory>   // for allocator
#include <sstream>  // for char_traits, basic_ost...

#include "mamba/__utils/hex_printer.hpp"       // for operator<<, print_hex
#include "mamba/builtins/__types/big_int.hpp"  // for BigInt
#include "mamba/builtins/__types/str.hpp"      // for Str, operator<<

namespace mamba::builtins::details {

Str Object::__Name__() const {
  return "object";
}

Str Object::__Repr__() const {
  std::ostringstream oss;

  oss << "<" << __Name__() << " object at " << __utils::print_hex(__Id__())
      << ">";

  return oss.str();
}

Str Object::__Str__() const {
  return __Repr__();
}

Bool Object::__Bool__() const {
  return true;
}

Bool Object::__Eq__(const self& other) const {
  return __Id__() == other.__Id__();
}

Object::operator bool() const {
  return __Bool__();
}

bool Object::operator==(const self& other) const {
  return __Eq__(other);
}
bool Object::operator!=(const self& other) const {
  return !this->operator==(other);
}

BigInt Object::operator~() const {
  return __Id__();
}

}  // namespace mamba::builtins::details
