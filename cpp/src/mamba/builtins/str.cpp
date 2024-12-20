#include "mamba/builtins/__types/str.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <string_view>

#include "mamba/builtins/__types/big_int.hpp"

namespace mamba::builtins::details {

Str::Str() : data_(std::make_shared<Data>()) {};
Str::Str(const char* s) : data_(std::make_shared<Data>(s)) {}
Str::Str(std::string s) : data_(std::make_shared<Data>(std::move(s))) {}

Str::operator std::string() const {
  return data_->s_;
}

Str Str::__Name__() const {
  return "string";
}

BigInt Str::__Id__() const {
  return reinterpret_cast<BigInt>(data_.get());
}

Bool Str::__Bool__() const {
  return !data_->s_.empty();
}

Str Str::__Repr__() const {
  // Effectively a deep copy
  return Str(data_->s_);
}

/// @note This is a new copy.
Str Str::__Str__() const {
  return __Repr__();
}

Bool Str::__Eq__(const Str& other) const {
  return data_->s_ == other.data_->s_;
}

Int Str::__Len__() const {
  return data_->s_.size();
}

/// @note For easy C++ comparison to strings.
bool Str::operator==(const std::string_view sv) const {
  return data_->s_ == sv;
}
bool Str::operator!=(const std::string_view sv) const {
  return !(*this == sv);
}

/// @brief C++ equality overload with other Mamba strings.
bool Str::operator==(const Str& other) const {
  return __Eq__(other);
}
bool Str::operator!=(const Str& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& oss, const Str& s) {
  oss << static_cast<std::string>(s);
  return oss;
}

}  // namespace mamba::builtins::details
