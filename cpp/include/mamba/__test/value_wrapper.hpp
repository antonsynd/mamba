#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/big_int.hpp"
#include "mamba/builtins/bool.hpp"
#include "mamba/builtins/float.hpp"
#include "mamba/builtins/int.hpp"
#include "mamba/builtins/object.hpp"
#include "mamba/builtins/str.hpp"

namespace mamba::__test {

template <builtins::__concepts::Value T>
struct Wrapper : public builtins::Object {
 public:
  using value_type = T;
  using self = Wrapper<value_type>;

  static void ResetId() { global_id_ = 0; }
  static std::size_t GetNextId() { return global_id_++; }

  explicit Wrapper(value_type value)
      : data_(std::make_shared<Data>(value, GetNextId())) {}

  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  std::size_t Id() const { return data_->id_; }
  value_type Value() const { return data_->v_; }

  operator value_type() const { return data_->v_; }

  builtins::StrType __Repr__() const override {
    std::ostringstream oss;
    oss << "[Wrapper(value=" << data_->v_ << ", id=" << data_->id_ << ")]";
    return oss.str();
  }

  builtins::BigIntType __Id__() const override {
    return reinterpret_cast<builtins::BigIntType>(data_.get());
  }

  builtins::BoolType __Bool__() const override { return true; }

  builtins::BoolType __Eq__(const self& other) const {
    return data_->v_ == other.data_->v_;
  }

  builtins::BoolType __Lt__(const self& other) const {
    return data_->v_ < other.data_->v_;
  }

  // Normally, these shouldn't be needed because of the global operator==()
  // definition in operators.hpp, but because this class has multiple implicit
  // conversions (value_type, and bool), it's necessary to help the compiler
  // avoid the ambiguity when invoking operator==() globally.
  bool operator==(const self& other) const { return __Eq__(other); }

  bool operator!=(const self& other) const { return !(*this == other); }

  bool operator<(const self& other) const { return __Lt__(other); }

 private:
  inline static std::size_t global_id_ = 0;

  class Data {
   public:
    T v_;
    size_t id_;
  };

  std::shared_ptr<Data> data_;
};

using IntWrapper = Wrapper<builtins::IntType>;
using FloatWrapper = Wrapper<builtins::FloatType>;

}  // namespace mamba::__test
