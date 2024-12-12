#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::details {

/// Object and Str are in the same header because they depend on each other.
/// An Object has methods that return a Str, and a Str is an Object.

// Forward-declaration
class Str;

class Object {
 public:
  /// @note Mamba-specific
  using self = Object;

  virtual ~Object() = default;

  virtual Str __Repr__() const = 0;

  // NOTE: Implemented below
  virtual Str __Str__() const;

  virtual Bool __Bool__() const = 0;

  virtual Bool __Eq__(const self& other) const {
    return __Id__() == other.__Id__();
  }

  virtual BigInt __Id__() const = 0;

  // For C++ implicit conversion to bool
  virtual operator bool() const { return __Bool__(); }

  // For C++ code generation, facilitating the identity operator `is` like so:
  // ~a == ~b where a and b are objects, not values.
  virtual BigInt operator~() const { return __Id__(); }
};

// TODO: Make it Unicode friendly
/// @note Str objects behave like objects but are treated as values.
class Str final : public Object {
 public:
  Str() : data_(std::make_shared<Data>()) {};
  Str(const char* s) : data_(std::make_shared<Data>(s)) {}
  Str(std::string s) : data_(std::make_shared<Data>(std::move(s))) {}

  operator std::string() const { return data_->s_; }

  BigInt __Id__() const override {
    return reinterpret_cast<BigInt>(data_.get());
  }

  Bool __Bool__() const override { return !data_->s_.empty(); }

  Str __Repr__() const override {
    // Effectively a deep copy
    return Str(data_->s_);
  }

  /// @note This is a new copy.
  Str __Str__() const override { return __Repr__(); }

  Bool __Eq__(const Str& other) const { return data_->s_ == other.data_->s_; }

  Int __Len__() const { return data_->s_.size(); }

  /// @note For easy C++ comparison to strings.
  bool operator==(const std::string_view sv) const { return data_->s_ == sv; }
  bool operator!=(const std::string_view sv) const { return !(*this == sv); }

 private:
  class Data {
   public:
    Data() = default;
    explicit Data(std::string s) : s_(std::move(s)) {}

    std::string s_;
  };

  std::shared_ptr<Data> data_;
};

inline Str Object::__Str__() const {
  return __Repr__();
}

}  // namespace mamba::builtins::details

// IWYU pragma: private
