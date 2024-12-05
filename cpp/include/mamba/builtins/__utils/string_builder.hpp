#pragma once

#include <sstream>
#include <string>

namespace mamba::builtins {

namespace details {

struct Flush {};

class StringBuilder {
 public:
  using self = StringBuilder;

  std::string operator<<(const Flush&) {
    auto res = oss_.str();

    oss_.clear();

    return res;
  }

  template <typename T>
  self& operator<<(T&& t) {
    oss_ << std::forward<T>(t);

    return *this;
  }

 private:
  std::ostringstream oss_;
};

}  // namespace details

using Flush = details::Flush;

details::StringBuilder stringify() {
  return details::StringBuilder();
}

}  // namespace mamba::builtins
