#pragma once

#include <memory>
#include <string>

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins::__types {

// TODO: Make it Unicode friendly
class Str final : public Object {
 public:
  using shared = std::shared_ptr<Str>;

  Str() = default;
  Str(std::string s) : s_(std::move(s)) {}

  operator std::string() const { return s_; }

  Bool __Bool__() const { return !s_.empty(); }
  Int __Len__() const { return s_.size(); }
  Bool __Eq__(const shared& other) const { return s_ == other->s_; }

  /// @note This is a new copy.
  shared __Str__() const { return __Repr__(); }

  shared __Repr__() const {
    // Invoke copy constructor
    return std::make_shared<Str>(*this);
  }

 private:
  std::string s_;
}

}  // namespace mamba::builtins::__types

// IWYU pragma: private
