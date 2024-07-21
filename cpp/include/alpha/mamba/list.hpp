#pragma once
#include <vector>

namespace mamba {

template <typename T>
class List {
 public:
  List() {}

  std::vector<T>& GetValue() const { return v_; }
  void SetValue(std::vector<T> v) { v_ = std::move(v); }

 private:
  mutable std::vector<T> v_;
};

}  // namespace mamba
