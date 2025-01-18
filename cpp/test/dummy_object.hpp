#pragma once

#include <cstddef>  // for size_t
#include <utility>  // for forward

#include "mamba/builtins/types.hpp"  // for ObjectType

namespace mamba::test {

struct DummyObject : public builtins::ObjectType {
 public:
  static void ResetId();
  static std::size_t GetNextId();

  DummyObject();

  template <typename... Args>
  static DummyObject __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  std::size_t Id() const;

 private:
  inline static std::size_t global_id_ = 0;

  class Data {
   public:
    size_t id_;
  };

  Data data_;
};

}  // namespace mamba::test
