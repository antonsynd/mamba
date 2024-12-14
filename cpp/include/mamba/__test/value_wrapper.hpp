#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/types.hpp"

namespace mamba::__test {

enum class EqualityMethod : int {
  kValueEquality = 0,
  kIdentity = 1,
};

template <builtins::details::Value T,
          EqualityMethod EM = EqualityMethod::kValueEquality>
struct Wrapper : public builtins::ObjectType {
 public:
  using value_type = T;
  static constexpr auto equality_method = EM;
  using self = Wrapper<value_type, equality_method>;

  static void ResetId() { global_id_ = 0; }
  static std::size_t GetNextId() { return global_id_++; }

  /// @note Mainly to satisfy contexts (e.g. std::vector.reserve()) where the
  /// default constructor needs to be invoked to reserve space.
  Wrapper() : data_(std::make_shared<Data>(value_type(), GetNextId())) {}

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
    if constexpr (self::equality_method == EqualityMethod::kValueEquality) {
      return data_->v_ == other.data_->v_;
    } else {
      return data_.get() == other.data_.get();
    }
  }

  builtins::BoolType __Lt__(const self& other) const {
    return data_->v_ < other.data_->v_;
  }

  // Normally, these shouldn't be needed because of the global operator
  // definitions in operators.hpp, but because this class has multiple implicit
  // conversions (value_type, and bool), it's necessary to help the compiler
  // avoid the ambiguity.
  bool operator==(const self& other) const { return __Eq__(other); }
  bool operator!=(const self& other) const { return !(*this == other); }
  bool operator<(const self& other) const { return __Lt__(other); }

  // Bring in superclass member functions for which there are overloads here
  using builtins::ObjectType::operator==;
  using builtins::ObjectType::operator!=;
  using builtins::ObjectType::__Eq__;

 private:
  inline static std::size_t global_id_ = 0;

  class Data {
   public:
    T v_;
    size_t id_;
  };

  std::shared_ptr<Data> data_;
};

template <builtins::details::Value T>
using IdentityWrapper = Wrapper<T, EqualityMethod::kIdentity>;

using IntWrapper = Wrapper<builtins::IntType>;
using FloatWrapper = Wrapper<builtins::FloatType>;

using IntIdentityWrapper = IdentityWrapper<builtins::IntType>;
using FloatIdentityWrapper = IdentityWrapper<builtins::FloatType>;

}  // namespace mamba::__test
