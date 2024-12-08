#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::__types {

// TODO: Make it Unicode friendly
/// @note Str objects behave like objects but are treated as values.
class Str final {
 public:
  Str() : data_(std::make_shared<Data>()) {};
  Str(const char* s) : data_(std::make_shared<Data>(s)) {}
  Str(std::string s) : data_(std::make_shared<Data>(std::move(s))) {}

  operator std::string() const { return data_->s_; }

  BigInt __Id__() const { return reinterpret_cast<BigInt>(data_.get()); }

  Bool __Bool__() const { return !data_->s_.empty(); }

  operator bool() const { return __Bool__(); }

  Str __Repr__() const {
    // Effectively a deep copy
    return Str(data_->s_);
  }

  /// @note This is a new copy.
  Str __Str__() const { return __Repr__(); }

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

}  // namespace mamba::builtins::__types

// IWYU pragma: private
