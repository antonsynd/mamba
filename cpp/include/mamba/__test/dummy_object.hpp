#pragma once

#include <memory>
#include <utility>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/big_int.hpp"
#include "mamba/builtins/bool.hpp"
#include "mamba/builtins/object.hpp"
#include "mamba/builtins/str.hpp"

namespace mamba::__test {

struct DummyObject : public builtins::Object {
 public:
  using self = DummyObject;

  static void ResetId() { global_id_ = 0; }
  static std::size_t GetNextId() { return global_id_++; }

  DummyObject() = default;

  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  std::size_t Id() const { return data_->id_; }

  builtins::StrType __Repr__() const override { return "DummyObject"; }

  builtins::BigIntType __Id__() const override {
    return reinterpret_cast<builtins::BigIntType>(data_.get());
  }

  builtins::BoolType __Bool__() const override { return true; }

  builtins::BoolType __Eq__(const self& other) const {
    return data_->id_ == other.data_->id_;
  }

 private:
  inline static std::size_t global_id_ = 0;

  class Data {
   public:
    size_t id_;
  };

  std::shared_ptr<Data> data_;
};

}  // namespace mamba::__test
