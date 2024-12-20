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

  std::string operator<<(const Flush&);

  template <NotFlush T>
  self& operator<<(const T& t) {
    oss_ << t;

    return *this;
  }

  operator std::string() const;

 private:
  std::ostringstream oss_;
};

}  // namespace details

using Flush = details::Flush;

details::StringBuilder stringify();

}  // namespace mamba::__utils
