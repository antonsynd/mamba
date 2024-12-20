#pragma once

#include <memory>
#include <string>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

class Str final : public Object {
 public:
  Str();
  Str(const char* s);
  Str(std::string s);

  operator std::string() const;

  Str __Name__() const override;

  BigInt __Id__() const override;

  Bool __Bool__() const override;

  Str __Repr__() const override;

  /// @note This is a new copy.
  Str __Str__() const override;

  Bool __Eq__(const Str& other) const;

  Int __Len__() const;

  /// @note For easy C++ comparison to strings.
  bool operator==(const std::string_view sv) const;
  bool operator!=(const std::string_view sv) const;

  /// @brief C++ equality overload with other Mamba strings.
  bool operator==(const Str& other) const;
  bool operator!=(const Str& other) const;

  // Bring in superclass member functions for which there are overloads here
  using Object::operator==;
  using Object::operator!=;
  using Object::__Eq__;

 private:
  class Data {
   public:
    Data() = default;
    explicit Data(std::string s) : s_(std::move(s)) {}

    std::string s_;
  };

  std::shared_ptr<Data> data_;
};

std::ostream& operator<<(std::ostream& oss, const Str& s);

template <>
struct Traits<Str> {
  static constexpr std::string_view kName = "str";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
