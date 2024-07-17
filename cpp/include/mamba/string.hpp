#pragma once
#include <string>

namespace mamba {

class String {
 public:
  String(std::string v = "") : v_(std::move(v)) {}

  const std::string& GetValue() const { return v_; }
  void SetValue(std::string v) { v_ = std::move(v); }

 private:
  std::string v_;
};

}  // namespace mamba
