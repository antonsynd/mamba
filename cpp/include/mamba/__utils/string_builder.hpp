#pragma once

#include <concepts>
#include <sstream>
#include <string>

namespace mamba::__utils {
namespace details {

struct Flush {};

template <typename T>
concept NotFlush = !std::derived_from<T, Flush>;

class StringBuilder {
 public:
  using self = StringBuilder;

  std::string operator<<(const Flush&) {
    auto res = oss_.str();

    oss_.clear();

    return res;
  }

  template <NotFlush T>
  self& operator<<(const T& t) {
    oss_ << t;

    return *this;
  }

  operator std::string() const { return oss_.str(); }

 private:
  std::ostringstream oss_;
};

}  // namespace details

using Flush = details::Flush;

inline details::StringBuilder stringify() {
  return details::StringBuilder();
}

}  // namespace mamba::__utils
