#include "mamba/builtins/__types/object.hpp"

#include <memory>   // for allocator
#include <sstream>  // for char_traits, basic_ost...

#include "mamba/__utils/hex_printer.hpp"    // for operator<<, print_hex
#include "mamba/builtins/__types/size.hpp"  // for Size
#include "mamba/builtins/__types/str.hpp"   // for Str, operator<<

namespace mamba::builtins::details {

Size Object::Id() const {
  return reinterpret_cast<Size>(this);
}

Str Object::_Repr(std::string name) const {
  std::ostringstream oss;

  oss << "<" << std::move(name) << " object at "
      << __utils::print_hex(reinterpret_cast<Size>(this)) << ">";

  return oss.str();
}

Str Object::Repr() const {
  return _Repr("object");
}

std::shared_ptr<Object> Object::_GetRef() {
  return shared_from_this();
}

Object::operator Str() const {
  return Repr();
}

bool Object::operator==(const Object& other) const {
  return this == &other;
}

bool Object::operator!=(const Object& other) const {
  return !this->operator==(other);
}

}  // namespace mamba::builtins::details
